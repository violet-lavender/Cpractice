#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

/*
0~9, 48~57
A~Z, 65~90
a~z, 97~122
自然有序, 不用排序
*/
#define LEN 75

void GetNTimesCharacter(int nValue, char **strings, int stringsSize, char *output, int outputSize)
{
    if (nValue <= 0 || stringsSize == 0) {
        output[0] = '\0';
        return;
    }
    // {0} 是唯一能直接初始化整个数组为零值的简短语法; {非零值} 只会初始化第一个元素, 其他都为0
    int minFreq[LEN];
    for (int i = 0; i < LEN; i++) {
        minFreq[i] = INT_MAX;
    }
    for (int i = 0; i < stringsSize; i++) {
        char *str = strings[i];
        int freq[LEN] = {0};
        for (int j = 0; str[j] != '\0'; j++) {
            freq[str[j] - '0']++;
        }
        for (int j = 0; j < LEN; j++) {
            if (freq[j] < minFreq[j]) {
                minFreq[j] = freq[j];
            }
        }
    }
    int index = 0;
    output[index++] = '[';
    bool first = true;
    for (int i = 0; i < LEN; i++) {
        if (minFreq[i] >= nValue && index < outputSize - 1) {
            if(!first) {
                output[index++] = ' ';
            }
            output[index++] = i + '0';
            first = false;
        }
    }
    if (index < outputSize - 1) {
        output[index++] = ']';
    }
    output[index] = '\0';
}