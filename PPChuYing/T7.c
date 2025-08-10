#include<stdlib.h>

#define MAX_NUM 100

typedef struct {
    int length;
    int priority;
} Bill;

int compareBill(const void *a, const void *b)
{
    Bill *ba = (const Bill *)a;
    Bill *bb = (const Bill *)b;
    if (ba->priority != bb->priority) {
        return ba->priority - bb->priority;
    }
    return ba->length - bb->length;
}

int GetMaxSendNumber(int cap, int num, int *bill, int *pri)
{
    if (num == 0) {
        return 0;
    }
    Bill bills[MAX_NUM];
    for (int i = 0; i < num; i++) {
        bills[i].length = bill[i];
        bills[i].priority = pri[i];
    }
    qsort(bills, num, sizeof(Bill), compareBill);
    int ret = 0;
    int len = 0;
    for (int i = 0; i < num; i++) {
        if (bills[i].length + len <= cap) {
            len += bills[i].length;
            ret++;
        } else {
            break;
        }
    }
    return ret;
}