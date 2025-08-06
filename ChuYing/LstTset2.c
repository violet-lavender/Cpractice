#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>

// 定义节点结构
typedef struct OrderNode
{
    int customerId;
    struct OrderNode *next;
} OrderNode;

// 每种商品的等待队列
typedef struct
{
    char name[11]; // 商品种类名
    OrderNode *head;
    OrderNode *tail;
} GoodsQueue;

#define MAX_CUSTOMERS 1001
#define MAX_GOODS 2003

typedef struct
{
    GoodsQueue goodsMap[MAX_GOODS]; // 每种商品的等待队列
    int goodsCount;                 // 当前商品种类数
    int pending[MAX_CUSTOMERS];     // 每个客户的未发货商品数
} OrderSystem;

// 工具：获取/添加商品队列索引
static int get_goods_index(OrderSystem *sys, const char *name)
{
    for (int i = 0; i < sys->goodsCount; ++i)
    {
        if (strcmp(sys->goodsMap[i].name, name) == 0)
            return i;
    }
    // 新增商品队列
    strcpy(sys->goodsMap[sys->goodsCount].name, name);
    sys->goodsMap[sys->goodsCount].head = NULL;
    sys->goodsMap[sys->goodsCount].tail = NULL;
    return sys->goodsCount++;
}

// 初始化
static OrderSystem *OrderSystemCreate(void)
{
    OrderSystem *sys = (OrderSystem *)calloc(1, sizeof(OrderSystem));
    return sys;
}

// 订货
static void OrderSystemOrder(OrderSystem *sys, int customerId, char **goods, size_t goodsSize)
{
    for (size_t i = 0; i < goodsSize; ++i)
    {
        int idx = get_goods_index(sys, goods[i]);
        // 创建节点
        OrderNode *node = (OrderNode *)malloc(sizeof(OrderNode));
        node->customerId = customerId;
        node->next = NULL;
        // 入队
        if (sys->goodsMap[idx].tail)
        {
            sys->goodsMap[idx].tail->next = node;
        }
        else
        {
            sys->goodsMap[idx].head = node;
        }
        sys->goodsMap[idx].tail = node;
        // 增加客户待发货数
        sys->pending[customerId]++;
    }
}

// 发货
static void OrderSystemDeliver(OrderSystem *sys, char **goods, size_t goodsSize)
{
    for (size_t i = 0; i < goodsSize; ++i)
    {
        int idx = get_goods_index(sys, goods[i]);
        GoodsQueue *q = &sys->goodsMap[idx];
        if (q->head)
        {
            OrderNode *node = q->head;
            int cid = node->customerId;
            sys->pending[cid]--;
            // 出队
            q->head = node->next;
            if (!q->head)
                q->tail = NULL;
            free(node);
        }
    }
}

// 查询
static int OrderSystemQuery(OrderSystem *sys)
{
    int maxPending = 0;
    int resId = -1;
    for (int i = 1; i < MAX_CUSTOMERS; ++i)
    {
        if (sys->pending[i] > maxPending)
        {
            maxPending = sys->pending[i];
            resId = i;
        }
        else if (sys->pending[i] == maxPending && maxPending > 0 && i < resId)
        {
            resId = i;
        }
    }
    return resId;
}

// 释放资源
static void OrderSystemFree(OrderSystem *sys)
{
    for (int i = 0; i < sys->goodsCount; ++i)
    {
        OrderNode *cur = sys->goodsMap[i].head;
        while (cur)
        {
            OrderNode *tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(sys);
}