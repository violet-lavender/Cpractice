int GetMinStep(const int *steps, int n)
{
    int total = 0;
    int prev = 0;
    for (int i = 0; i < n; ++i)
    {
        if (steps[i] > prev)
        {
            total += steps[i] - prev;
        }
        prev = steps[i];
    }
    return total;
}
