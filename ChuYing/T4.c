#include <string.h>

int BinaryToDecimal(char *binaryString)
{
    if (binaryString == NULL || *binaryString == '\0')
    {
        return 0;
    }

    int result = 0;
    for (int i = 0; binaryString[i] != '\0'; i++)
    {
        result = result << 1; // 等价于 result *= 2
        if (binaryString[i] == '1')
        {
            result += 1;
        }
    }
    return result;
}