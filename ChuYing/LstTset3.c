#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id1;
    int id2;
} DependInfo;

static int GetMinTime(int taskNum, const DependInfo *relations, size_t relationsSize)
{
    // 建图
    int *inDegree = (int *)calloc(taskNum + 1, sizeof(int));
    int **adj = (int **)malloc((taskNum + 1) * sizeof(int *));
    int *adjSize = (int *)calloc(taskNum + 1, sizeof(int));
    int *adjCap = (int *)calloc(taskNum + 1, sizeof(int));

    for (int i = 0; i <= taskNum; ++i)
    {
        adjCap[i] = 4;
        adj[i] = (int *)malloc(adjCap[i] * sizeof(int));
    }

    for (size_t i = 0; i < relationsSize; ++i)
    {
        int from = relations[i].id2;
        int to = relations[i].id1;
        if (adjSize[from] == adjCap[from])
        {
            adjCap[from] *= 2;
            adj[from] = (int *)realloc(adj[from], adjCap[from] * sizeof(int));
        }
        adj[from][adjSize[from]++] = to;
        inDegree[to]++;
    }

    // 拓扑排序 + 动态规划计算每个任务的最早完成时间
    int *queue = (int *)malloc(taskNum * sizeof(int));
    int front = 0, rear = 0;
    int *time = (int *)calloc(taskNum + 1, sizeof(int));

    for (int i = 1; i <= taskNum; ++i)
    {
        if (inDegree[i] == 0)
        {
            queue[rear++] = i;
            time[i] = 1; // 无依赖的任务可以立即开始，耗时1
        }
    }

    while (front < rear)
    {
        int curr = queue[front++];
        for (int i = 0; i < adjSize[curr]; ++i)
        {
            int next = adj[curr][i];
            if (time[next] < time[curr] + 1)
                time[next] = time[curr] + 1;
            if (--inDegree[next] == 0)
                queue[rear++] = next;
        }
    }

    int maxTime = 0;
    for (int i = 1; i <= taskNum; ++i)
    {
        if (time[i] > maxTime)
            maxTime = time[i];
    }

    // 释放内存
    for (int i = 0; i <= taskNum; ++i)
        free(adj[i]);
    free(adj);
    free(adjSize);
    free(adjCap);
    free(inDegree);
    free(queue);
    free(time);

    return maxTime;
}