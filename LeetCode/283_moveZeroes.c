void moveZeroes(int* nums, int numsSize)
{
    int i = 0, j = 0;
    for (; j < numsSize; j++)
    {
        if (nums[j] != 0)
        {
            nums[i] = nums[j];
            i++;
        }
    }
    for (; i < numsSize; i++)
    {
        nums[i] = 0;
    }
}