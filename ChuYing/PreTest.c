#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 比特翻转, 滑动窗口
static int FindMaxConsecutiveBits(int target, const int *bits, size_t bitsSize)
{
    int max_len = 0;
    int left = 0;
    int flip_count = 0;

    for (int right = 0; right < bitsSize; right++) {
        // 如果当前位不是 target 则翻转
        if (bits[right]!= target) {
            flip_count++;
        }

        // 如果翻转次数超过一次 则移动左边界
        while (flip_count > 1) {
            if (bits[left] != target) {
                flip_count--;
            }
            left++;
        }

        // 更新最大长度
        int current_len = right - left + 1;
        if (current_len > max_len)
        {
            max_len = current_len;
        }
    }
    return max_len;
}
