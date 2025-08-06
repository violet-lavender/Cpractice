#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

void GetHexString(const char *inputStr, char *output, int outputSize)
{
    // 转换为64位整数
    char *endptr;
    long long num = strtoll(inputStr, &endptr, 10);

    // 检查转换有效性
    if (endptr == inputStr || *endptr != '\0')
    {
        snprintf(output, outputSize, "overflow");
        return;
    }

    // 检查范围
    const long long minVal = -2147483648LL; // -2^31
    const long long maxVal = 4294967295LL;  // 2^32-1
    if (num < minVal || num > maxVal)
    {
        snprintf(output, outputSize, "overflow");
        return;
    }

    // 转换为32位无符号整数（自动处理负数补码）
    uint32_t value;
    if (num < 0)
    {
        // 负数直接转换为补码
        value = (uint32_t)num;
    }
    else
    {
        value = (uint32_t)num;
    }

    // 提取字节
    uint8_t bytes[4];
    bytes[0] = (value >> 24) & 0xFF; // 最高位字节
    bytes[1] = (value >> 16) & 0xFF;
    bytes[2] = (value >> 8) & 0xFF;
    bytes[3] = value & 0xFF; // 最低位字节

    // 准备输出缓冲区
    char bigEndian[12]; // 4字节*2字符 + 3空格 + 1结束符
    char smallEndian[12];

    // 格式化大端序
    snprintf(bigEndian, sizeof(bigEndian), "%02X %02X %02X %02X",
             bytes[0], bytes[1], bytes[2], bytes[3]);

    // 格式化小端序
    snprintf(smallEndian, sizeof(smallEndian), "%02X %02X %02X %02X",
             bytes[3], bytes[2], bytes[1], bytes[0]);

    // 组合最终输出
    snprintf(output, outputSize, "%s\n%s", bigEndian, smallEndian);
}