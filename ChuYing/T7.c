#include <stdio.h>
#include <stdlib.h>

// 话单结构体
struct Bill
{
    int length;
    int priority;
};

// 比较函数：先按优先级升序，再按长度升序
int cmp(const void *a, const void *b)
{
    struct Bill *ba = (struct Bill *)a;
    struct Bill *bb = (struct Bill *)b;
    if (ba->priority != bb->priority)
        return ba->priority - bb->priority;
    return ba->length - bb->length;
}

int GetMaxSendNumber(int cap, int num, int *bill, int *pri)
{
    if (num == 0 || cap <= 0)
        return 0;

    struct Bill bills[100];
    for (int i = 0; i < num; ++i)
    {
        bills[i].length = bill[i];
        bills[i].priority = pri[i];
    }

    // 排序：优先级升序 -> 长度升序
    qsort(bills, num, sizeof(struct Bill), cmp);

    int totalLen = 0, count = 0;
    for (int i = 0; i < num; ++i)
    {
        if (totalLen + bills[i].length <= cap)
        {
            totalLen += bills[i].length;
            count++;
        }
        else
        {
            break; // 再往后长度更大或相等，且优先级更低
        }
    }

    return count;
}
