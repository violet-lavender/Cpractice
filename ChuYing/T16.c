#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static uint8_t *SimpleCheckSum(const uint8_t *data, size_t dataSize, size_t *returnSize)
{
    // 计算补齐后长度，补0xFF字节
    size_t paddedLen = ((dataSize + 3) / 4) * 4;

    // 分配缓冲区保存补齐数据
    uint8_t *buffer = malloc(paddedLen);
    if (!buffer)
        return NULL;

    // 复制原始数据
    memcpy(buffer, data, dataSize);

    // 补齐0xFF
    for (size_t i = dataSize; i < paddedLen; i++)
    {
        buffer[i] = 0xFF;
    }

    // 如果只有4字节，直接返回（校验和就是这4字节）
    if (paddedLen == 4)
    {
        *returnSize = 4;
        return buffer;
    }

    // 多于4字节，进行异或计算
    uint32_t checksum = 0;
    for (size_t i = 0; i < paddedLen; i += 4)
    {
        uint32_t val =
            ((uint32_t)buffer[i] << 24) |
            ((uint32_t)buffer[i + 1] << 16) |
            ((uint32_t)buffer[i + 2] << 8) |
            ((uint32_t)buffer[i + 3]);

        checksum ^= val;
    }

    // 将结果拆回4字节，放到buffer前4字节
    buffer[0] = (checksum >> 24) & 0xFF;
    buffer[1] = (checksum >> 16) & 0xFF;
    buffer[2] = (checksum >> 8) & 0xFF;
    buffer[3] = checksum & 0xFF;

    *returnSize = 4;
    return buffer;
}
