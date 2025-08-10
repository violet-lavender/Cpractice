#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 经典滑动窗口。每次更新窗口后，窗口中所有以 right 为结束字符的子串都是有效的，数量是 right - left + 1
int GetCountOfSubString(char *str)
{
    int n = strlen(str);
    int l = 0, r = 0;
    int ret = 0;
    bool exist[26] = {false};
    while (r < n) {
        while (exist[str[r] - 'a']) {
            exist[str[l] - 'a'] = false;
            l++;
        }
        exist[str[r] - 'a'] = true;
        ret += r - l + 1;
        r++;
    }
    return ret;
}