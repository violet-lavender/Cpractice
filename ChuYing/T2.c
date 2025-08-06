#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STR_LEN 16
#define ARR_MAX_LEN 1000

static int cmp_str(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

static int cmp_value(const void *a, const void *b)
{
    const char *strA = *(const char **)a;
    const char *strB = *(const char **)b;
    unsigned long numA = strtoul(strA, NULL, 16);
    unsigned long numB = strtoul(strB, NULL, 16);
    if (numA < numB)
        return -1;
    if (numA > numB)
        return 1;
    return strcmp(strA, strB);
}

static int GetAllFault(char **arrayA, int arrayASize, char **arrayB, int arrayBSize,
                       char outBuf[][STR_LEN], int maxOutBufLen)
{
    int totalSize = arrayASize + arrayBSize;
    if (totalSize == 0)
    {
        return 0;
    }

    char **total = (char **)malloc(totalSize * sizeof(char *));
    if (total == NULL)
    {
        return 0;
    }

    int index = 0;
    for (int i = 0; i < arrayASize; i++)
    {
        total[index++] = arrayA[i];
    }
    for (int i = 0; i < arrayBSize; i++)
    {
        total[index++] = arrayB[i];
    }

    qsort(total, totalSize, sizeof(char *), cmp_str);

    int uniqueCount = 0;
    if (totalSize > 0)
    {
        uniqueCount = 1;
        for (int i = 1; i < totalSize; i++)
        {
            if (strcmp(total[i], total[i - 1]) != 0)
            {
                total[uniqueCount++] = total[i];
            }
        }
    }

    if (uniqueCount > 1)
    {
        qsort(total, uniqueCount, sizeof(char *), cmp_value);
    }

    int copyCount = uniqueCount < maxOutBufLen ? uniqueCount : maxOutBufLen;
    for (int i = 0; i < copyCount; i++)
    {
        strncpy(outBuf[i], total[i], STR_LEN - 1);
        outBuf[i][STR_LEN - 1] = '\0';
    }

    free(total);
    return uniqueCount;
}