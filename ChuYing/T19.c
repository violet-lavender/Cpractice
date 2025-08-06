#include <string.h>
#include <ctype.h>

int isVowel(char c)
{
    char lower = c | 32; // 快速转小写
    return lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u';
}

int GetLongestFlawedVowelSubstrLen(int flaw, char *str)
{
    int maxLen = 0;
    int left = 0, right = 0;
    int nonVowelCount = 0;
    int len = strlen(str);

    while (right < len)
    {
        // Expand right
        if (!isVowel(str[right]))
        {
            nonVowelCount++;
        }

        // Shrink from left if flaw exceeded
        while (nonVowelCount > flaw)
        {
            if (!isVowel(str[left]))
            {
                nonVowelCount--;
            }
            left++;
        }

        // Check if current window is valid
        if (isVowel(str[left]) && isVowel(str[right]) && nonVowelCount == flaw)
        {
            int currLen = right - left + 1;
            if (currLen > maxLen)
            {
                maxLen = currLen;
            }
        }

        right++;
    }

    return maxLen;
}
