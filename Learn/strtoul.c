
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>

/*
strtoul 函数用于将字符串转换为无符号长整型, 定义在头文件 <stdlib.h> 中

unsigned long int strtoul(
    const char *str,     // 要转换的字符串. 指向待转换的字符串的指针, 跳过开头的空白字符(如空格、制表符等)
    char **endptr,       // 指向首个无效字符的指针. 二级指针, 用于存储首个无法转换的字符地址; 若传入 NULL,则不保存该信息
    int base             // 进制基数 (0 或 2~36).0: 自动检测进制（前缀0x为十六进制，0为八进制, 否则十进制）;2~36: 显式指定进制.
                            若字符串包含无效字符(如 base=10 时遇到字母), 转换停止; 字符串带负号(如 "-1")会转换为无符号的补码值(即 ULONG_MAX)
);
返回值
成功转换: 返回对应的无符号长整型值。
错误情况:
    无有效数字 → 返回 0;
    值超出范围 → 返回 ULONG_MAX(定义在 <limits.h>), 并设置 errno 为 ERANGE.
*/

int main()
{
    const char *str = "99999999999999999999"; // 超出 ULONG_MAX
    char *end;
    unsigned long val;

    errno = 0; // 重置错误标志
    val = strtoul(str, &end, 10);

    if (errno == ERANGE)
    {
        printf("数值超出范围！\n");
        printf("返回值: %lu (ULONG_MAX=%lu)\n", val, ULONG_MAX);
    }
    else if (end == str)
    {
        printf("无有效数字！\n");
    }
    else
    {
        printf("转换结果: %lu\n", val);
    }

    return 0;
}