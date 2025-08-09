#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stdio.h>

void GetHexString(const char *inputStr, char *output, int outputSize)
{
    char *end;
    long long num = strtoll(inputStr, &end, 10);    // strtoul返回值是unsigned long int, 需要转换
    if (end == inputStr || *end != '\0') {
        strcpy(output, "overflow");
        return;
    }

    // 用 stdint.h 中定义的宏, 或者用 math.h 中的幂运算 pow() (返回值为 double)
    if (num < INT32_MIN || num > UINT32_MAX)
    {
        strcpy(output, "overflow");
        return;
    }

    // 移位操作. 左移<<, 右侧补 0; 右移>> 无符号左侧补 0（逻辑右移）, 有符号左侧补符号位（算术右移）
    uint32_t val = (uint32_t)num;
    uint8_t bytes[4];
    bytes[0] = num >> 24; // 最高字节位, 类型转换截断时丢弃高位, 保留低位; 截断始终针对数值的二进制表示（小端/大端系统结果相同）
    bytes[1] = num >> 16;
    bytes[2] = num >> 8;
    bytes[3] = num;

    char bigEndian[12], smallEndian[12];    // 4 * 2 + 3空格 + 1结束符
    // 格式化: %02X, 最小宽度为2, 用0填充空白, 大写16进制
    snprintf(bigEndian, sizeof(bigEndian),"%02X %02X %02X %02X", bytes[0], bytes[1], bytes[2], bytes[3]);
    snprintf(smallEndian, sizeof(bigEndian), "%02X %02X %02X %02X", bytes[3], bytes[2], bytes[1], bytes[0]);
    snprintf(output, outputSize, "%s\n%s", bigEndian, smallEndian);
}