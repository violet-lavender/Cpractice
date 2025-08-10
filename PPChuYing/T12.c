#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比较巧妙的解决

#define SECOND_LEN 20 // "YYYY-MM-DD hh:mm:ss" 19 + '\0'; 完整是"YYYY-MM-DD hh:mm:ss.fff"

typedef struct {
    char second[SECOND_LEN];
    int minMs;
    int count;
} Records;

int FreeOrder(char **orderTime, int orderTimeSize) {
    Records *records = (Records *) malloc(orderTimeSize * sizeof(Records));
    int recordCount = 0;
    for (int i = 0; i < orderTimeSize; i++) {
        char second[SECOND_LEN];
        strncpy(second, orderTime[i], SECOND_LEN - 1);
        second[SECOND_LEN - 1] = '\0';
        int ms = atoi(orderTime[i] + 20);
        int found = 0;
        for (int j = 0; j < recordCount; j++) {
            if (strcmp(records[j].second, second) == 0) {
                if (ms < records[j].minMs) {
                    records[j].minMs = ms;
                    records[j].count = 1;
                } else if (ms == records[j].minMs) {
                    records[j].count++;
                }
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy(records[recordCount].second, second);
            records[recordCount].minMs = ms;
            records[recordCount].count = 1;
            recordCount++;
        }
    }
    int ret = 0;
    for (int i = 0; i < recordCount; i++) {
        ret += records[i].count;
    }
    free(records);
    return ret;
}