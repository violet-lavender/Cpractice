#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../CLibs/uthash/include/uthash.h"

/*
特性	strcpy	strdup
内存管理	不分配内存	动态分配内存
目标缓冲区	必须预先分配	自动创建
返回值	目标缓冲区的指针	新分配内存的指针
安全性	可能缓冲区溢出	避免溢出（分配足够空间）
内存释放	不需要特殊释放	必须调用 free() 释放
标准符合性	C89/C99 标准函数	POSIX 扩展函数
函数复杂度	O(n) - 仅复制操作	O(n) - 分配内存+复制
错误处理	不返回错误	内存不足时返回 NULL
char *strcpy(char *dest, const char *src);
char *strdup(const char *s);
*/

/*
在 C 语言中，解引用操作符(*) 和 数组索引操作符([]) 本质上都是指针降维操作:

解引用(*ptr): 获取指针指向的值（降一维）
索引(ptr[i]): 等价于 *(ptr + i)（先指针算术运算再解引用，降一维）


(*returnColumnSizes)[i] = cur->size;
res[i++] = cur->list;

前者需要先*解引用，而后者不用

returnColumnSizes 是二级指针，需要先解引用(*)获取数组指针，然后索引([i])访问元素，最终得到 int 类型
res 是三级指针，直接索引([i])就降维到二级指针(char**)，与 cur->list 类型匹配
解引用和索引都是指针降维操作，选择取决于需要降维的次数和目标类型
最终目标是确保赋值操作符(=)两边的类型完全一致
*/

int compareChars(const void *a, const void *b) {
    return (*(const char *)a - *(const char *)b);
}

typedef struct {
    char key[101];  // 排序后的字符串为 key
    char **list;    // 字符串数组. 原地排序, 要存储原字符串的指针数组.
    int size;       // 当前组内字符串数量
    int capacity;   // 数组容量
    UT_hash_handle hh;
}hashTable;


char ***groupAnagrams(char **strs, int strsSize, int *returnSize, int **returnColumnSizes)
{
    hashTable *hash = NULL;
    *returnSize = 0;

    for (int i = 0; i < strsSize; i++) {
        char *str = strs[i];
        char *sorted = strdup(str);
        if (strlen(sorted) > 0) {
            qsort(sorted, strlen(sorted), sizeof(char), compareChars);
        }

        hashTable *item = NULL;
        HASH_FIND_STR(hash, sorted, item);

        if (item == NULL) {
            item = (hashTable *)malloc(sizeof(hashTable));
            if (item == NULL) {
                free(sorted);
                continue;
            }
            strncpy(item->key, sorted, sizeof(item->key) - 1);
            item->key[sizeof(item->key) - 1] = '\0';
            item->capacity = 10;
            item->size = 0;
            item->list = (char **)malloc(item->capacity * sizeof(char *));
            if (item->list == NULL) {
                free(item);
                free(sorted);
                continue;
            }
            item->list[item->size++] = str;
            HASH_ADD_STR(hash, key, item);
        } else {
            if (item->size == item->capacity) {
                item->capacity *= 2;
                char **newList = (char **)realloc(item->list, item->capacity * sizeof(char *));
                if (newList == NULL) {
                    free(sorted);
                    continue;
                }
                item->list = newList;
            }
            item->list[item->size++] = str;
        }
        free(sorted);
    }
    int groupSize = HASH_COUNT(hash);
    *returnSize = groupSize;
    *returnColumnSizes = (int *)malloc(groupSize * sizeof(int));
    char ***res = (char ***)malloc(groupSize * sizeof(char **));

    hashTable *cur, *tmp;
    int i = 0;
    HASH_ITER(hh, hash, cur, tmp) {
        (*returnColumnSizes)[i] = cur->size;
        /* 在C语言内存管理中，遵循单一所有权原则:
            每块动态分配的内存应有唯一的所有者
            所有权可以转移，但不能共享
            所有者负责内存的释放
            从哈希表中删除并释放结构体, 不释放list数组
        */
        res[i++] = cur->list;
        HASH_DEL(hash, cur);
        free(cur);
    }

    return res;
}