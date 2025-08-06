#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SECOND_LEN 20 // "YYYY-MM-DD hh:mm:ss"
#define HASH_SIZE 65536   

typedef struct
{
    char second[MAX_SECOND_LEN];
    int minMs;
    int count;
} Record;

int FreeOrder(char **orderTime, int orderTimeSize)
{
    Record *records = malloc(sizeof(Record) * orderTimeSize);
    int recCount = 0;

    for (int i = 0; i < orderTimeSize; ++i)
    {
        char second[MAX_SECOND_LEN];
        strncpy(second, orderTime[i], 19);
        second[19] = '\0';

        int ms = atoi(orderTime[i] + 20);

        // 查找是否已有该“秒”的记录
        int found = 0;
        for (int j = 0; j < recCount; ++j)
        {
            if (strcmp(records[j].second, second) == 0)
            {
                if (ms < records[j].minMs)
                {
                    records[j].minMs = ms;
                    records[j].count = 1;
                }
                else if (ms == records[j].minMs)
                {
                    records[j].count++;
                }
                found = 1;
                break;
            }
        }

        if (!found)
        {
            strcpy(records[recCount].second, second);
            records[recCount].minMs = ms;
            records[recCount].count = 1;
            recCount++;
        }
    }

    int total = 0;
    for (int i = 0; i < recCount; ++i)
    {
        total += records[i].count;
    }

    free(records);
    return total;
}
