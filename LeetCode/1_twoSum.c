#include <stdlib.h>
#include "../CLibs/uthash/include/uthash.h"

typedef struct
{
    int key;
    int value;
    UT_hash_handle hh;
}HashTable;

HashTable *hashtable = NULL;

HashTable *find(int ikey)
{
    HashTable *tmp = NULL;
    HASH_FIND_INT(hashtable, &ikey, tmp);
    return tmp;
}

void insert(int ikey, int ival)
{
    HashTable *ptr = find(ikey);
    if (ptr == NULL)
    {
        HashTable *tmp = malloc(sizeof(HashTable));
        tmp->key = ikey;
        tmp->value = ival;
        HASH_ADD_INT(hashtable, key, tmp);
    }
    else
    {
        ptr->value = ival;
    }
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    hashtable = NULL;   // 初始化哈希, 避免多次调用导致的数据残留; 可以使用局部变量, 然后参数传递**HashTable
    int i = 0;
    for(; i < numsSize; i++)
    {
        HashTable *ptr = find(target - nums[i]);
        if (ptr != NULL)
        {
            int *res = malloc(2 * sizeof(int));
            res[0] = ptr->value;
            res[1] = i;
            *returnSize = 2;
            return res;
        }
        insert(nums[i], i);
    }
    *returnSize = 0;
    return NULL;
}