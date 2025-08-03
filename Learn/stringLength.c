#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main() {
    char *str1 = "asdfgh";
    char str2[] = "asdfgh";
    char str3[8] = {'a', 's', 'd'};
    char str4[] = "as\0df";

    printf("sizeof(str1) = %d, strlen(str1) = %d\n", sizeof(str1), strlen(str1));
    printf("sizeof(str2) = %d, strlen(str2) = %d\n", sizeof(str2), strlen(str2));
    printf("sizeof(str3) = %d, strlen(str3) = %d\n", sizeof(str3), strlen(str3));
    printf("sizeof(str4) = %d, strlen(str4) = %d\n", sizeof(str4), strlen(str4));

    return 0;
}