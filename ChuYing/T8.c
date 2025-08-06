// 统计无重复字符子串
/* 给定一字符串，请统计位置连续，且无重复字符出现的子串数量。例如abc是无重复字符的子串，abb不是。
注：内容一样但位置不一样的子串，按不同子串参与统计。*/

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 经典滑动窗口。每次更新窗口后，窗口中所有以 right 为结束字符的子串都是有效的，数量是 right - left + 1
int GetCountOfSubString(char *str)
{
    int n = strlen(str);
    int count = 0;
    int left = 0;
    bool exist[256] = {false}; 

    for (int right = 0; right < n; ++right)
    {
        // 如果字符已经存在，移动左指针并移除重复字符
        while (exist[(unsigned char)str[right]])
        {
            exist[(unsigned char)str[left]] = false;
            left++;
        }

        // 标记当前字符
        exist[(unsigned char)str[right]] = true;

        // 当前窗口内的所有子串都是合法的无重复字符子串，子串个数等于窗口长度
        count += (right - left + 1);
    }

    return count;
}
