
#include <stdio.h>
#include <string.h>

struct RegInfo {
    int status;
    char *phNum;
};


static void Calling(const char *userStatus, const struct RegInfo *regInfos, int regInfoCnt,char *outBuf, int maxOutBufLen)
{
    char *map[5] = {NULL};
    for (int i = 0; i < regInfoCnt; i++) {
        int type = regInfos[i].status;
        map[type] = regInfos[i].phNum;
    }

    if (map[0] != NULL) {
        strcpy(outBuf, map[0]);
        return;
    }

    if (strcmp(userStatus, "busy") == 0 && map[1] != NULL) {
        strcpy(outBuf, map[1]);
        return;
    }

    if (strcmp(userStatus, "no-response") == 0 && map[2] != NULL) {
        strcpy(outBuf, map[2]);
        return;
    }

    if (strcmp(userStatus, "unreachable") == 0 && map[3] != NULL)
    {
        strcpy(outBuf, map[3]);
        return;
    }

    if (strcmp(userStatus, "idle") == 0) {
        strcpy(outBuf, "success");
        return;
    }

    if (map[4] != NULL) {
        strcpy(outBuf, map[4]);
        return;
    }

    strcpy(outBuf, "failure");
}
