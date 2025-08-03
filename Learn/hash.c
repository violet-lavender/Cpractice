#include "../CLibs/uthash/include/uthash.h"

typedef struct {
    int key;
    int value;  // 可以只有key没有value
    UT_hash_handle hh;
} Hash;

// 这个结构体没有标签, typedef定义了别名Hash, 声明时只能通过Hash即类型别名声明
// 有标签时，才可以通过struct Hash即结构体标签声明

Hash *hashtable = NULL;

Hash *HashFind(int key)
{
    Hash *ptr = NULL;
    HASH_FIND_INT(hashtable, &key, ptr);
    return ptr;
}

void HashInsert(int key, int value)
{
    Hash *ptr = HashFind(key);
    if (ptr == NULL)
    {
        Hash *tmp = malloc(sizeof(Hash));
        tmp->key = key;
        tmp->value = value;
        HASH_ADD_INT(hashtable, key, tmp);
    }
    else
    {
        ptr->value = value;
    }
}

int HashDelete(int key) 
{
    Hash *ptr = HashFind(key);
    if (ptr != NULL)
    {
        HASH_DEL(hashtable, ptr);
        free(ptr);
        ptr = NULL;    // free之后一定要置空
        return 1;
    }
    else
    {
        return 0;
    }
}