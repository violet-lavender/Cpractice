#include "../CLibs/uthash/include/uthash.h"

/*
核心接口操作:
HASH_ADD_INT(hashtable, key, tmp);  // 添加元素. 参数: 哈希表指针、key值、添加节点指针
HASH_FIND_INT(hashtable, &key, tmp);    // 参数: 哈希表指针、key值地址、返回节点指针
HASH_DEL(hashtable, tmp);   // 删除节点. 参数: 哈希表指针、删除节点指针
HASH_ITER(hh, hashtable, cur, tmp);   // 遍历哈希表. 参数: hh、哈希表指针、当前节点指针、临时节点指针
HASH_COUNT(hashtable);   // 获取元素个数. 参数: 哈希表指针
HASH_SORT(hashtable, cmp);   // 排序. 参数: 哈希表指针、compare函数

注意事项:
1.哈希表必须初始化为 NULL
2.UThash不自动处理键冲突
3.添加后修改键会破坏哈希, 需要先删除, 修改, 再添加
4.必须释放内存, HASH_DEL 后手动 free
5.多线程不安全
*/

typedef struct {
    int key;    // key、value 都可以是任意类型
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