#include <stdio.h>

/*
 1. 在计算机中，整数（包括有符号数和无符号数）都是以二进制形式存储的。对于有符号数，通常采用补码表示法。
 2. 补码表示法中，最高位是符号位（0表示正数，1表示负数），而负数的补码是通过其绝对值的二进制表示取反加一得到。
 3. 当我们将一个有符号的负数转换为无符号数时，计算机并不改变其存储的二进制位，而是直接将这些二进制位重新解释为无符号数。
 4. 在无符号数中，所有的位都是数值位，没有符号位。因此，原来补码中的符号位（即最高位）现在被当作数值的一部分。
*/

int main()
{
    int signed_val = -1;
    unsigned int unsigned_val = (unsigned int)signed_val;

    printf("补码表示: 0x%X\n", signed_val);
    printf("有符号值: %d\n", signed_val);
    printf("无符号值: %u\n", unsigned_val); // 直接读取补码

    // 验证等价公式
    int N = sizeof(int) * 8;
    unsigned int calc_val = signed_val + (1U << N);
    printf("公式计算: %u\n", calc_val); // 与直接转换相同

    return 0;
}