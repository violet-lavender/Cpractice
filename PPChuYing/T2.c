#include <stdlib.h>
#include <string.h>

#define STR_LEN 16
#define ARR_MAX_LEN 1000

static int compareStr(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

static int GetAllFault(char **arrayA, int arrayASize, char **arrayB, int arrayBSize,
                       char outBuf[][STR_LEN], int maxOutBufLen)
{
    int totalSize = arrayASize + arrayBSize;

    if (totalSize == 0)
    {
        return 0;
    }

    char **array = (char **)malloc(totalSize * sizeof(char *));
    if (array == NULL)
    {
        return 0;
    }
    int index = 0;
    for (int i = 0; i < arrayASize; i++)
    {
        array[index++] = arrayA[i];
    }
    for (int i = 0; i < arrayBSize; i++)
    {
        array[index++] = arrayB[i];
    }

    qsort(array, totalSize, sizeof(char *), compareStr);

    int uniqueIndex = 1;
    for (int i = 1; i < totalSize; i++) {
        if (strcmp(array[i], array[i - 1]) != 0) {
            array[uniqueIndex++] = array[i];
        }
    }

    int retCount = uniqueIndex < maxOutBufLen ? uniqueIndex : maxOutBufLen;
    for (int i = 0; i < retCount; i++) {
        strncpy(outBuf[i], array[i], STR_LEN - 1);
        outBuf[i][STR_LEN - 1] = '\0';
    }
    free(array);
    return uniqueIndex;
}