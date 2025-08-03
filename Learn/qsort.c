#include <stdlib.h>
#include  <string.h>
#include <stdio.h>

/*
void qsort(void *base,
           size_t nmemb,
           size_t size,
           int (*compar)(const void *, const void *));

base: 指向待排序数组的首元素的指针（数组名）
类型为 void*, 可接受任何类型的指针

nmemb: 数组中元素的数量

size: 每个元素的大小(字节数), 通常用 sizeof 运算符获取

compar: 指向比较函数的指针, 用于定义排序规则
函数签名: int compar(const void *a, const void *b)
比较函数规则:
比较函数必须返回整数:
< 0: a 应排在 b 前面
> 0: a 应排在 b 后面
= 0: a 和 b 相等(顺序不确定)
即 a -b 升序, b - a 降序
*/

int compare_ints(const void *a, const void *b)
{
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);   // 避免溢出
}

int compare_strings(const void *a, const void *b)
{
    // 这里 a、b 都是指向指针的指针. 字符串本身是指针, 而 compare 的参数是指向比较类型的指针 
    const char **str1 = (const char **)a;
    const char **str2 = (const char **)b;
    return strcmp(*str1, *str2);
}

typedef struct {
    char name[20];
    int age;
} Person;

int compare_age(const void *a, const void *b) {
    Person *p1 = (Person *)a;
    Person *p2 = (Person *)b;
    return p1->age - p2->age;
}

int main() {
    int arr[] = { 4, 2, 9, 1, 5};
    qsort(arr, sizeof(arr) / sizeof(arr[0]), sizeof(int), compare_ints);
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    char *names[] = { "Alice", "Bob", "Charlie", "David", "Eve" };
    qsort(names, sizeof(names) / sizeof(names[0]), sizeof(char *), compare_strings);
    for (size_t i = 0; i < sizeof(names) / sizeof(names[0]); i++) {
        printf("%s ", names[i]);
    }
    printf("\n");

    Person people[] = {
        { "Alice", 25 },
        { "Bob", 30 },
        { "Charlie", 20 }
    };
    qsort(people, sizeof(people) / sizeof(people[0]), sizeof(Person), compare_age);
    for (size_t i = 0; i < sizeof(people) / sizeof(people[0]); i++) {
        printf("%s: %d\n", people[i].name, people[i].age);
    }

    return 0;
}