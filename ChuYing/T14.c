#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int str_case_cmp(const char *a, const char *b)
{
    while (*a && *b)
    {
        if (tolower(*a) != tolower(*b))
            return tolower(*a) - tolower(*b);
        a++, b++;
    }
    return *a - *b;
}

int endsWithIP(const char *key)
{
    int len = strlen(key);
    return len >= 2 && tolower(key[len - 2]) == 'i' && tolower(key[len - 1]) == 'p';
}

int isInList(const char *key, char **keys, int keyCnt)
{
    for (int i = 0; i < keyCnt; ++i)
    {
        if (str_case_cmp(key, keys[i]) == 0)
            return 1;
    }
    return 0;
}

int isIPv4(const char *value)
{
    int seg = 0;
    const char *p = value;
    while (*p)
    {
        int num = 0, cnt = 0;
        while (*p && isdigit(*p))
        {
            num = num * 10 + (*p - '0');
            ++cnt;
            ++p;
        }
        if (cnt == 0 || num > 255)
            return 0;
        if (*p == '.')
            ++p, ++seg;
        else
            break;
    }
    return seg == 3 && *p == '\0';
}

void maskIPv4(const char *ip, char *buf)
{
    int part = 0;
    const char *p = ip;
    while (*p)
    {
        int start = strlen(buf);
        while (*p && *p != '.')
        {
            if ((part == 1 || part == 2))
            {
                strcat(buf, "*");
            }
            else
            {
                strncat(buf, p, 1);
            }
            ++p;
        }
        if (*p == '.')
        {
            strcat(buf, ".");
            ++p;
            ++part;
        }
    }
}

void maskNumber(char *value, char *buf)
{
    int len = strlen(value), i = len - 1;
    int end = -1, start = -1;

    while (i >= 0)
    {
        if (isdigit(value[i]))
        {
            end = i;
            while (i >= 0 && isdigit(value[i]))
                --i;
            start = i + 1;
            break;
        }
        --i;
    }

    if (start != -1)
    {
        int L = end - start + 1;
        int maskStart = end - (L / 4);
        int maskEnd = maskStart - (L / 2) + 1;

        for (int i = 0; i < len; ++i)
        {
            if (i >= maskEnd && i <= maskStart && isdigit(value[i]))
            {
                buf[i] = '*';
            }
            else
            {
                buf[i] = value[i];
            }
        }
        buf[len] = '\0';
    }
    else
    {
        strcpy(buf, value); // no digit substring
    }
}

void LogAnonymize(char *keys[], int keyCnt, char *input, char *outBuf, int outBufLen)
{
    char *p = input;
    char field[256];
    int outPos = 0;

    while (*p)
    {
        int len = 0;
        while (*p && *p != ',')
            field[len++] = *p++;
        field[len] = '\0';
        if (*p == ',')
            ++p;

        // split key and value
        char *colon = strchr(field, ':');
        if (!colon)
            continue;
        *colon = '\0';
        char *key = field;
        char *value = colon + 1;

        char lowerKey[64];
        for (int i = 0; key[i]; ++i)
            lowerKey[i] = tolower(key[i]);
        lowerKey[strlen(key)] = '\0';

        int isSensitive = 0;
        char processedValue[256];

        // Rule 1: password/pwd
        if (str_case_cmp(key, "password") == 0 || str_case_cmp(key, "pwd") == 0)
        {
            strcpy(processedValue, "******");
            isSensitive = 1;
        }
        // Rule 2: in words list
        else if (isInList(key, keys, keyCnt))
        {
            isSensitive = 1;
            if (endsWithIP(key) && isIPv4(value))
            {
                processedValue[0] = '\0';
                maskIPv4(value, processedValue);
            }
            else
            {
                maskNumber(value, processedValue);
            }
        }

        // compose output
        int n = snprintf(outBuf + outPos, outBufLen - outPos, "%s:%s", key, isSensitive ? processedValue : value);
        outPos += n;

        // add comma if not end
        if (*p)
        {
            if (outPos < outBufLen - 1)
            {
                outBuf[outPos++] = ',';
                outBuf[outPos] = '\0';
            }
        }
    }
}
