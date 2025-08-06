#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int start;
    int end; // end is exclusive
} Interval;

static int cmpInterval(const void *a, const void *b)
{
    Interval *ia = (Interval *)a;
    Interval *ib = (Interval *)b;
    return ia->start - ib->start;
}

static char *GetTaggedString(char **words, size_t wordsSize, const char *inputStr)
{
    size_t inputLen = strlen(inputStr);

    // 最多所有词每个位置都匹配一次，最多wordsSize * inputLen个区间，保守估计
    Interval *intervals = malloc(sizeof(Interval) * wordsSize * inputLen);
    if (!intervals)
        return NULL;
    int intervalCount = 0;

    // 查找每个关键词在inputStr中的所有出现位置
    for (size_t i = 0; i < wordsSize; i++)
    {
        char *pos = (char *)inputStr;
        size_t wordLen = strlen(words[i]);
        while (1)
        {
            char *found = strstr(pos, words[i]);
            if (!found)
                break;
            int start = (int)(found - inputStr);
            int end = start + (int)wordLen;
            intervals[intervalCount].start = start;
            intervals[intervalCount].end = end;
            intervalCount++;
            pos = found + 1; // 继续往后找，允许重叠
        }
    }

    if (intervalCount == 0)
    {
        // 没有任何关键词出现，直接返回原字符串
        free(intervals);
        char *res = malloc(inputLen + 1);
        if (!res)
            return NULL;
        strcpy(res, inputStr);
        return res;
    }

    // 对区间排序
    qsort(intervals, intervalCount, sizeof(Interval), cmpInterval);

    // 合并区间
    Interval *merged = malloc(sizeof(Interval) * intervalCount);
    if (!merged)
    {
        free(intervals);
        return NULL;
    }
    int mergedCount = 0;

    merged[0] = intervals[0];
    for (int i = 1; i < intervalCount; i++)
    {
        if (intervals[i].start <= merged[mergedCount].end)
        {
            // 重叠或相邻(因为end是exclusive， intervals[i].start == merged[mergedCount].end时也应该合并)
            if (intervals[i].end > merged[mergedCount].end)
            {
                merged[mergedCount].end = intervals[i].end;
            }
        }
        else
        {
            mergedCount++;
            merged[mergedCount] = intervals[i];
        }
    }
    mergedCount++; // 最终区间数

    // 根据合并区间插入标签
    // 结果最长可能为inputLen + 7 * mergedCount，留足够空间
    size_t maxResultLen = inputLen + mergedCount * 7 + 1;
    char *result = malloc(maxResultLen);
    if (!result)
    {
        free(intervals);
        free(merged);
        return NULL;
    }

    size_t resPos = 0;
    int intervalIdx = 0;
    for (size_t i = 0; i < inputLen; i++)
    {
        // 判断是否在合并区间开始
        if (intervalIdx < mergedCount && i == (size_t)merged[intervalIdx].start)
        {
            memcpy(result + resPos, "<b>", 3);
            resPos += 3;
        }

        result[resPos++] = inputStr[i];

        // 判断是否在合并区间结束（end是exclusive）
        if (intervalIdx < mergedCount && i == (size_t)merged[intervalIdx].end - 1)
        {
            memcpy(result + resPos, "</b>", 4);
            resPos += 4;
            intervalIdx++;
        }
    }
    result[resPos] = '\0';

    free(intervals);
    free(merged);

    return result;
}
