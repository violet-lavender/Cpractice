#include<stdlib.h>

static int GetLongestNum(long long num)
{
    if (num == 0 || num == 1) {
        return 1;
    }

    int maxLen = 1;
    int curLen = 0;
    int preBit = -1;    // 初始化为不可能取到的 -1, 因此curLen初始化为不可能的 0 而不是1, 后续每次重置为 1 
    while (num > 0)
    {
        int bit = num & 1;
        if (bit == preBit) {
            curLen++;
        } else {
            curLen = 1;
            preBit = bit;
        }
        if (curLen > maxLen) {
            maxLen = curLen;
        }
        // 移位操作. 左移<<, 右侧补 0; 右移>> 无符号左侧补 0（逻辑右移）, 有符号左侧补符号位（算术右移）
        // 移位操作符(>> 和 <<)是 非破坏性操作, 它们会返回一个新的结果值, 但不会修改原始操作数
        num >>= 1;
    }
    return maxLen;
}