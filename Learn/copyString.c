/*
将字符串字面量 "hello" 赋值给 char *str时
1. 直接赋值：str = "hello";
    char *str = "hello";  // 注意：应加const（const char*）更安全

        内存位置：字符串位于只读数据段（.rodata）

        可修改性：尝试修改内容（如str[0]='H'）会导致未定义行为（通常是段错误）

        内存管理：无需手动释放

        特点：最高效，但最不安全

2. 内存分配 + strcpy/strncpy

    str = malloc(6);       // 手动分配堆内存
    strcpy(str, "hello");  // 或 strncpy(str, "hello", 6);

        内存位置：字符串位于堆内存

        可修改性：内容可安全修改（如str[0]='H'）

        内存管理：必须手动free(str)，否则内存泄漏

        特点：

            strcpy有溢出风险（如果分配空间不足）

            strncpy更安全但需处理边界（不会自动补\0）

3. strdup（POSIX标准）

    str = strdup("hello");  // 非C标准库（但广泛支持）
        内存位置：字符串位于堆内存（内部调用malloc）

        可修改性：内容可安全修改

        内存管理：必须手动free(str)

        特点：

            等效于malloc+strcpy的封装

            简洁但非C标准（需#define _POSIX_C_SOURCE）

4. 内存分配 + sprintf/snprintf

    str = malloc(6);
    sprintf(str, "hello");   // 危险！
    snprintf(str, 6, "hello"); // 安全版
        内存位置：字符串位于堆内存

        可修改性：内容可修改

        内存管理：必须手动free(str)

        特点：

            sprintf极度危险（无长度检查，缓冲区溢出风险）

            snprintf安全但大材小用（适合格式化，单纯复制字符串效率低）

内存来源:栈内存、堆内存、静态内存、字面量
只有 strdup 会自动创建内存, 但是都需要调用者管理内存, 堆上内存都需要free

在 '\0'处理上: 直接赋值字面量自带'\0'
strcpy, 需分配长度+1的空间, 长度不够会溢出
strncpy, 可能缺失, 必须手动添加或确保长度足够
strdup, 最简洁的安全方式
sprintf, 与strcpy一致, 也有溢出风险
snprintf, 截断时也保证'\0'（只要size>0）
*/