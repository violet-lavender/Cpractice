#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    int start;
    int load;
} MsgInfo;

// 小根堆结构，存储忙碌服务器 (finishTime, serverId)
typedef struct
{
    long long finishTime;
    int serverId;
} HeapNode;

typedef struct
{
    HeapNode *data;
    int size;
    int capacity;
} MinHeap;

MinHeap *createHeap(int capacity)
{
    MinHeap *h = malloc(sizeof(MinHeap));
    h->data = malloc(sizeof(HeapNode) * capacity);
    h->size = 0;
    h->capacity = capacity;
    return h;
}

void swap(HeapNode *a, HeapNode *b)
{
    HeapNode tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapPush(MinHeap *h, long long finishTime, int serverId)
{
    if (h->size >= h->capacity)
        return;
    h->data[h->size].finishTime = finishTime;
    h->data[h->size].serverId = serverId;
    int i = h->size++;
    while (i > 0)
    {
        int p = (i - 1) / 2;
        if (h->data[p].finishTime < h->data[i].finishTime ||
            (h->data[p].finishTime == h->data[i].finishTime && h->data[p].serverId < h->data[i].serverId))
            break;
        swap(&h->data[p], &h->data[i]);
        i = p;
    }
}

void heapPop(MinHeap *h)
{
    if (h->size == 0)
        return;
    h->data[0] = h->data[--h->size];
    int i = 0;
    while (1)
    {
        int smallest = i;
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < h->size && (h->data[l].finishTime < h->data[smallest].finishTime ||
                            (h->data[l].finishTime == h->data[smallest].finishTime && h->data[l].serverId < h->data[smallest].serverId)))
            smallest = l;
        if (r < h->size && (h->data[r].finishTime < h->data[smallest].finishTime ||
                            (h->data[r].finishTime == h->data[smallest].finishTime && h->data[r].serverId < h->data[smallest].serverId)))
            smallest = r;
        if (smallest == i)
            break;
        swap(&h->data[i], &h->data[smallest]);
        i = smallest;
    }
}

HeapNode heapTop(MinHeap *h)
{
    return h->data[0];
}

// 二分查找第一个>= val 的元素的下标，没找到返回 -1
int binarySearch(int *arr, int size, int val)
{
    int left = 0, right = size - 1, ans = -1;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if (arr[mid] >= val)
        {
            ans = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    return ans;
}

// 从空闲服务器数组中删除指定服务器编号
void removeServer(int *arr, int *size, int serverId, int pos)
{
    // pos 为serverId在arr中的下标
    memmove(&arr[pos], &arr[pos + 1], (*size - pos - 1) * sizeof(int));
    (*size)--;
}

static int *HighestLoadServers(int serverNum, const MsgInfo *messages, size_t messagesSize, size_t *returnSize)
{
    int *loads = calloc(serverNum, sizeof(int));

    // 空闲服务器编号数组，初始填充0~serverNum-1
    int *freeServers = malloc(serverNum * sizeof(int));
    int freeSize = serverNum;
    for (int i = 0; i < serverNum; i++)
        freeServers[i] = i;

    // 小根堆，维护忙碌服务器 (finishTime, serverId)
    MinHeap *busyHeap = createHeap((int)messagesSize);

    for (int i = 0; i < (int)messagesSize; i++)
    {
        int start = messages[i].start;
        int load = messages[i].load;

        // 释放所有已完成服务器
        while (busyHeap->size > 0 && heapTop(busyHeap).finishTime <= start)
        {
            HeapNode top = heapTop(busyHeap);
            heapPop(busyHeap);
            // 放回空闲服务器数组（保持有序）
            // 二分插入
            int left = 0, right = freeSize;
            while (left < right)
            {
                int mid = (left + right) / 2;
                if (freeServers[mid] < top.serverId)
                    left = mid + 1;
                else
                    right = mid;
            }
            memmove(&freeServers[left + 1], &freeServers[left], (freeSize - left) * sizeof(int));
            freeServers[left] = top.serverId;
            freeSize++;
        }

        if (freeSize == 0)
        {
            // 全忙，丢弃
            continue;
        }

        // 计算优先分配服务器编号起点（i % serverNum）
        int preferred = i % serverNum;
        // 找空闲服务器中第一个编号 >= preferred 的服务器
        int pos = binarySearch(freeServers, freeSize, preferred);
        int assignedServer = -1;
        if (pos == -1)
        {
            // 没有>=preferred的，选第一个编号
            assignedServer = freeServers[0];
            removeServer(freeServers, &freeSize, assignedServer, 0);
        }
        else
        {
            assignedServer = freeServers[pos];
            removeServer(freeServers, &freeSize, assignedServer, pos);
        }

        loads[assignedServer] += load;
        long long finishTime = (long long)start + load;
        heapPush(busyHeap, finishTime, assignedServer);
    }

    // 找最大负载
    int maxLoad = 0;
    for (int i = 0; i < serverNum; i++)
    {
        if (loads[i] > maxLoad)
            maxLoad = loads[i];
    }

    // 统计结果服务器编号，编号从1开始
    int *result = malloc(serverNum * sizeof(int));
    int cnt = 0;
    for (int i = 0; i < serverNum; i++)
    {
        if (loads[i] == maxLoad)
        {
            result[cnt++] = i + 1;
        }
    }

    free(loads);
    free(freeServers);
    free(busyHeap->data);
    free(busyHeap);

    *returnSize = cnt;
    return result;
}
