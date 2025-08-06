#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b)
{
    int *x = (int *)a;
    int *y = (int *)b;
    if (x[0] != y[0])
        return x[0] - y[0]; // 按start升序
    return y[1] - x[1];     // start相同，按end降序
}

int GetMinPeople(int questionsCount, int peopleCount, int correctRange[][2])
{
    qsort(correctRange, peopleCount, sizeof(correctRange[0]), cmp);

    int currentEnd = 0;
    int index = 0;
    int count = 0;

    while (currentEnd < questionsCount)
    {
        int maxEnd = currentEnd;
        while (index < peopleCount && correctRange[index][0] <= currentEnd + 1)
        {
            if (correctRange[index][1] > maxEnd)
            {
                maxEnd = correctRange[index][1];
            }
            index++;
        }

        if (maxEnd == currentEnd)
        {
            return -1; // 无法扩展覆盖范围
        }

        currentEnd = maxEnd;
        count++;
    }

    return count;
}
