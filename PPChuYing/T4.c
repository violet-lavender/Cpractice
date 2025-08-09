#include<stdlib.h>
#include<string.h>

int BinaryToDecimal(char *binaryString)
{
    long int num = strtoll(binaryString, NULL, 2);
    return (int)num;
}