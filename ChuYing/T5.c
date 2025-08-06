#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int Calc(const char *input)
{
    int len = strlen(input);
    if (len == 0)
        return 0;

    // 初始化栈
    int stack_capacity = 10000;
    int *stack = (int *)malloc(stack_capacity * sizeof(int));
    if (stack == NULL)
        return 0;
    int top = -1;

    int i = 0;
    while (i < len)
    {
        // 定位当前token的结束位置
        int j = i;
        while (j < len && input[j] != ',')
            j++;
        int token_len = j - i;

        // 处理运算符
        if (token_len == 1 &&
            (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'))
        {
            if (top < 1)
            {
                free(stack);
                return 0; // 栈中操作数不足，但题目保证合法，此情况不应发生
            }
            int right = stack[top--];
            int left = stack[top--];
            int result;
            switch (input[i])
            {
            case '+':
                result = left + right;
                break;
            case '-':
                result = left - right;
                break;
            case '*':
                result = left * right;
                break;
            case '/':
                result = left / right;
                break; // 整数除法（向零取整）
            }
            stack[++top] = result;
        }
        // 处理操作数
        else
        {
            long long num = 0;
            int sign = 1;
            int start = i;

            // 处理负数
            if (input[i] == '-')
            {
                sign = -1;
                start = i + 1; // 跳过负号
            }

            // 转换字符串为整数
            for (int k = start; k < j; k++)
            {
                num = num * 10 + (input[k] - '0');
            }
            num = sign * num;

            // 栈扩容检查
            if (top + 1 >= stack_capacity)
            {
                stack_capacity *= 2;
                int *new_stack = (int *)realloc(stack, stack_capacity * sizeof(int));
                if (new_stack == NULL)
                {
                    free(stack);
                    return 0;
                }
                stack = new_stack;
            }
            stack[++top] = (int)num;
        }
        i = j + 1; // 跳过逗号
    }

    int result = stack[top];
    free(stack);
    return result;
}