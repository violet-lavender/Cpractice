#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    char *str1 = "asdfgh";
    char str2[] = "asdfgh";
    char str3[8] = {'a', 's', 'd'};
    char str4[] = "as\0df";

    printf("sizeof(str1) = %d, strlen(str1) = %d\n", sizeof(str1), strlen(str1));
    printf("sizeof(str2) = %d, strlen(str2) = %d\n", sizeof(str2), strlen(str2));
    printf("sizeof(str3) = %d, strlen(str3) = %d\n", sizeof(str3), strlen(str3));
    printf("sizeof(str4) = %d, strlen(str4) = %d\n", sizeof(str4), strlen(str4));

    return 0;
}

/*
str1 是字符指针变量, sizeof 获得的是该指针所占的地址空间;
    strlen 返回的是该字符串的长度, 遇到 \0 结束, \0 本身不计算在内, 结果是 6.

str2 是字符数组, 大小由字符串常量 "asdfgh" 确定, sizeof 获得该数组所占内存空间大小, 包括字符串结尾的 \0 , 所以结果为 7;
    strlen 同理返回 6.

str3 也是字符数组, 但大小确定为 8, 故 sizeof 得到的结果是 8; 
    strlen 统计 \0 之前所有字符的个数, 即为 3；

str4 是常量字符数组, sizeof 得到字符总数即 6; 
    strlen 计算至 \0 结束, 因此返回 2;

sizeof 计算的是变量的大小, 而 strlen 计算的是字符串的长度, 前者不受字符 \0 影响, 后者以 \0 作为长度判定依据.
*/