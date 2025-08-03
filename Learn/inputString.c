# include <stdio.h>
# include <string.h>

# define MAX_LEN 100

/*
1、fgets

防止缓冲区溢出（指定最大长度）

读取整行（包括空格）

标准C函数，跨平台

注意：会保留换行符（需手动移除）

2、 带保护的 scanf()

已知输入格式且无空格时可用 %s

需读取包含空格的字符串时用 %[^\n]

使用`%99s`读取一个不带空格的字符串（遇到空格会停止）。如果要读取包含空格的整行，可以使用`%[^\n]`，但同样要指定宽度。

需手动处理缓冲区残留

不如 fgets 直观安全
*/

int main() {
    char buffer[MAX_LEN];

    printf("Enter a string: ");
    if (fgets(buffer, sizeof(buffer), stdin) != NULL)
    {
        // strcspn(str1, str2) 查找子串, 
        buffer[strcspn(buffer, "\n")] = '\0'; 
        printf("You entered: %s\n", buffer);
    }
    else
    {
        printf("Error reading input\n");
    }

    char str[100];
    printf("Enter a string: ");
    if (scanf("%99[^\n]", str) == 1)
    {
        while (getchar() != '\n'); // 处理输入缓冲区残留
        printf("You entered: %s\n", str);
    }
    else {
        printf("Error reading input\n");
    }
    
    return 0;
}