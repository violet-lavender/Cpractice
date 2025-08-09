#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<stdio.h>

/* 这不是一个典型的利用栈进行表达式求解, 它在真正的表达式中用括号限制了优先级, 在后序序列中 
不用考虑优先级问题, 只要有两个操作数和一个运算符就可以计算, 一个栈就可以解决, 同时序列中只有数字和运算符;
*/
#define MAX_LEN 50000

typedef struct 
{
    int vals[MAX_LEN];
    int top;
}Stack;

void push(Stack *stack, int val) {
    stack->top++;
    stack->vals[stack->top] = val;
}

int pop(Stack *stack) {
    if (stack->top < 0) {
        return -1 ;
    }
    int ret = stack->vals[stack->top];
    stack->top--;
    return ret;
}

int getTop(Stack *stack) {
    if (stack->top < 0) {
        return - 1;
    }
    return stack->vals[stack->top];
}

bool isOperator(char ch) 
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/'; 
}

int cal(int a, int b, char o)
{
    switch (o)
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
}


static int Calc(const char *input)
{
    int len = strlen(input);
    if (len == 0) {
        return 0;
    }
    Stack stack = {{0}, -1};
    int i = 0;
    // 题目保证表达式合法, 遍历整个表达式作循环即可
    while (i < len) {
        int j = i;
        // j 停留的始终是 ',' 或者 '\0', 不要做索引
        while (j < len && input[j] != ',') {
            j++;
        }
        int tokenLen = j - i;
        if (tokenLen == 1 && isOperator(input[i])) {
            int right = pop(&stack);
            int left = pop(&stack);
            push(&stack, cal(left, right, input[i]));
        } else {
            int num = 0;
            int start = i;
            int sign = 1;   // 用 sign 表示正负, 最后乘即可, 不用 bool
            if (input[i] == '-') {
                sign = -1;
                start++;
            }
            for (int k = start; k < j; k++) {
                num = num * 10 + (input[k] - '0');  // 注意这里 input[k] - '0'
            }
            num *= sign; 
            push(&stack, num);
        }
        i = j + 1;
    }
    return pop(&stack);
}