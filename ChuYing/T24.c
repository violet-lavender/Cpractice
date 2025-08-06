#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 比较函数用于 qsort
int cmp(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

// 二分判断 x 是否在 nums[0..n-1]
bool isFail(int *nums, int n, int x)
{
    return bsearch(&x, nums, n, sizeof(int), cmp) != NULL;
}

int BatchCalculation(int *nums, int n, int m)
{
    // 对失败批次排序
    qsort(nums, n, sizeof(int), cmp);

    int maxLen = 0;
    int left = 1, right = 1;
    int failCount = 0;

    while (right <= 10000)
    {
        if (isFail(nums, n, right))
        {
            failCount++;
        }

        // 如果失败超过可纠错次数，缩小左边界
        while (failCount > m)
        {
            if (isFail(nums, n, left))
            {
                failCount--;
            }
            left++;
        }

        // 更新最大长度
        int curLen = right - left + 1;
        if (curLen > maxLen)
        {
            maxLen = curLen;
        }

        right++;
    }

    return maxLen;
}
