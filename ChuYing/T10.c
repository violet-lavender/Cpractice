// 字符排序
/* 给定一个字符串, 仅含英文字母和数字
排序后，原位置是数字的，排序后仍然是数字；原位置是字母的，排序后仍然是字母。
数字：按 0-9 升序; 英文字母：大写字母大于小写字母，小写字母按 a-z 升序，大写字母按 A-Z 升序。 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int cmpChar(const void *a, const void *b)
{
    char c1 = *(char *)a;
    char c2 = *(char *)b;
    int isLower1 = islower(c1);
    int isLower2 = islower(c2);

    if (isLower1 != isLower2)
    {
        return isLower1 ? -1 : 1; // 小写在前
    }
    else
    {
        return c1 - c2;
    }
}

int cmpDigit(const void *a, const void *b)
{
    return *(char *)a - *(char *)b;
}

void CharacterSort(char *inputStr, char *output, int outputSize)
{
    int len = strlen(inputStr);
    if (outputSize <= len)
    {
        output[0] = '\0';
        return;
    }

    char letters[1000];
    char digits[1000];
    int letterIdx = 0, digitIdx = 0;

    // 第一次遍历：提取字母和数字
    for (int i = 0; i < len; ++i)
    {
        if (isalpha(inputStr[i]))
        {
            letters[letterIdx++] = inputStr[i];
        }
        else if (isdigit(inputStr[i]))
        {
            digits[digitIdx++] = inputStr[i];
        }
    }

    // 排序
    qsort(letters, letterIdx, sizeof(char), cmpChar);
    qsort(digits, digitIdx, sizeof(char), cmpDigit);

    // 第二次遍历：按原样类别写入 output
    int li = 0, di = 0;
    for (int i = 0; i < len; ++i)
    {
        if (isalpha(inputStr[i]))
        {
            output[i] = letters[li++];
        }
        else if (isdigit(inputStr[i]))
        {
            output[i] = digits[di++];
        }
    }
    output[len] = '\0';
}