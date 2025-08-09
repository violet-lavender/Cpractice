#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_LEN 1000

int compareDigit(const void *a, const void *b) {
    return *(const char*)a - *(const char *)b;
}

int compareChar(const void *a, const void *b) {
    char c1 = *(const char *)a, c2 = *(const char *)b;
    int isLower1 = islower(c1), isLower2 = islower(c2);
    if (isLower1 != isLower2) {
        return isLower1 ? -1 : 1;   // 小写在前
    }
    return c1 - c2;
}

void CharacterSort(char *inputStr, char *output, int outputSize)
{
    int len = strlen(inputStr);
    char letters[MAX_LEN], digits[MAX_LEN];
    int letterIndex = 0, digitIndex = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(inputStr[i])) {
            letters[letterIndex++] = inputStr[i];
        } else if(isdigit(inputStr[i])) {
            digits[digitIndex++] = inputStr[i];
        }
    }
    qsort(letters, letterIndex, sizeof(char), compareChar);
    qsort(digits, digitIndex, sizeof(char), compareDigit);
    letterIndex = 0, digitIndex = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(inputStr[i])) {
            output[i] = letters[letterIndex++];
        } else if (isdigit(inputStr[i])) {
            output[i] = digits[digitIndex++];
        }
    }
    output[len] = '\0';
}