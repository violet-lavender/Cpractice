static int GetLongestNum(long long num)
{
    if (num == 0)
        return 1; // 二进制为 "0"，长度为 1

    int maxLen = 0;
    int currentLen = 0;
    int prevBit = -1;

    while (num > 0)
    {
        int bit = num & 1;
        if (bit == prevBit)
        {
            currentLen++;
        }
        else
        {
            currentLen = 1;
            prevBit = bit;
        }
        if (currentLen > maxLen)
        {
            maxLen = currentLen;
        }
        num >>= 1;
    }

    return maxLen;
}
