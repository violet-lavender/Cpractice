#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007

typedef struct
{
    int t;
    int p;
} TaskInfo;

// 比较函数：先按优先级升序，若优先级相同则执行时间降序
int cmpTask(const void *a, const void *b)
{
    TaskInfo *ta = (TaskInfo *)a;
    TaskInfo *tb = (TaskInfo *)b;
    if (ta->p != tb->p)
        return ta->p - tb->p;
    return tb->t - ta->t;
}

// 小根堆操作
void heapify_down(long long *heap, int n, int i)
{
    int smallest = i;
    int l = 2 * i + 1, r = 2 * i + 2;
    if (l < n && heap[l] < heap[smallest])
        smallest = l;
    if (r < n && heap[r] < heap[smallest])
        smallest = r;
    if (smallest != i)
    {
        long long temp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = temp;
        heapify_down(heap, n, smallest);
    }
}

void heapify_up(long long *heap, int i)
{
    while (i > 0)
    {
        int parent = (i - 1) / 2;
        if (heap[i] >= heap[parent])
            break;
        long long temp = heap[i];
        heap[i] = heap[parent];
        heap[parent] = temp;
        i = parent;
    }
}

int TaskScheduler(int m, int n, TaskInfo *info)
{
    qsort(info, n, sizeof(TaskInfo), cmpTask);

    // 初始化最小堆，表示每台VM的可用时间
    long long *heap = (long long *)malloc(sizeof(long long) * m);
    for (int i = 0; i < m; ++i)
        heap[i] = 0;

    int heapSize = m;
    long long maxTime = 0;

    for (int i = 0; i < n; ++i)
    {
        // 取出当前最早空闲的VM
        long long earliest = heap[0];
        long long newTime = earliest + info[i].t;
        if (newTime > maxTime)
            maxTime = newTime;

        // 更新堆顶为新的空闲时间
        heap[0] = newTime;
        heapify_down(heap, heapSize, 0);
    }

    free(heap);
    return (int)(maxTime % MOD);
}
