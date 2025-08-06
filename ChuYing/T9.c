// 公共字符
// 给定 m 个字符串计算有哪些字符在所有字符串中都出现过 n 次及以上。n [1,100]，m [1,100]，str[1,1000)
// 按ASCII码升序输出所有符合要求的字符序列； 如果没有符合要求的字符，则输出空序列[]
#include <stdio.h>
#include <string.h>
#include <limits.h>

void GetNTimesCharacter(int nValue, char **strings, int stringsSize, char *output, int outputSize)
{
    if (stringsSize == 0 || nValue <= 0 || outputSize <= 0)
    {
        if (outputSize > 0)
            output[0] = '\0';
        return;
    }

    int minFreq[256]; // 最小出现次数，初始化为最大值
    for (int i = 0; i < 256; ++i)
    {
        minFreq[i] = INT_MAX;
    }

    for (int i = 0; i < stringsSize; ++i)
    {
        int freq[256] = {0};

        // 统计每个字符在当前字符串中出现的次数
        for (char *p = strings[i]; *p != '\0'; ++p)
        {
            unsigned char c = (unsigned char)(*p);
            freq[c]++;
        }

        // 更新 minFreq
        for (int j = 0; j < 256; ++j)
        {
            if (freq[j] < minFreq[j])
            {
                minFreq[j] = freq[j];
            }
        }
    }

    int outIndex = 0;
    output[outIndex++] = '[';
    int first = 1;

    for (int i = 0; i < 256; ++i)
    {
        if (minFreq[i] >= nValue)
        {
            if (!first)
            {
                if (outIndex < outputSize - 1)
                    output[outIndex++] = ' ';
            }
            if (outIndex < outputSize - 1)
                output[outIndex++] = (char)i;
            first = 0;
        }
    }

    if (outIndex < outputSize - 1)
        output[outIndex++] = ']';
    output[outIndex] = '\0';            
}
