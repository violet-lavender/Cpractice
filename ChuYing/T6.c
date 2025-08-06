#include <stdio.h>
#include <string.h>

struct RegInfo
{
    int status;  // type: 0~4
    char *phNum; // 转移号码
};

static void Calling(const char *userStatus, const struct RegInfo *regInfos, int regInfoCnt,
                    char *outBuf, int maxOutBufLen)
{
    // 保存每种 type 对应的最后一个转移号码（NULL 表示未登记）
    const char *map[5] = {NULL};

    // 记录最新转移号码
    for (int i = 0; i < regInfoCnt; ++i)
    {
        int type = regInfos[i].status;
        map[type] = regInfos[i].phNum; // 以最后一次登记为准
    }

    // 优先级判断
    if (map[0] != NULL)
    {
        strncpy(outBuf, map[0], maxOutBufLen - 1);
        outBuf[maxOutBufLen - 1] = '\0';
        return;
    }

    if (strcmp(userStatus, "busy") == 0 && map[1] != NULL)
    {
        strncpy(outBuf, map[1], maxOutBufLen - 1);
        outBuf[maxOutBufLen - 1] = '\0';
        return;
    }

    if (strcmp(userStatus, "no-response") == 0 && map[2] != NULL)
    {
        strncpy(outBuf, map[2], maxOutBufLen - 1);
        outBuf[maxOutBufLen - 1] = '\0';
        return;
    }

    if (strcmp(userStatus, "unreachable") == 0 && map[3] != NULL)
    {
        strncpy(outBuf, map[3], maxOutBufLen - 1);
        outBuf[maxOutBufLen - 1] = '\0';
        return;
    }

    if (strcmp(userStatus, "idle") == 0)
    {
        strncpy(outBuf, "success", maxOutBufLen - 1);
        outBuf[maxOutBufLen - 1] = '\0';
        return;
    }

    if (map[4] != NULL)
    {
        strncpy(outBuf, map[4], maxOutBufLen - 1);
        outBuf[maxOutBufLen - 1] = '\0';
        return;
    }

    // 无法转移、非 idle 状态，则失败
    strncpy(outBuf, "failure", maxOutBufLen - 1);
    outBuf[maxOutBufLen - 1] = '\0';
}
