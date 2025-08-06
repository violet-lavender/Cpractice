// 遥控小车
/* 假设在平面直角坐标系中一个遥控小车最初位于原点 (0, 0) 处，且面朝北方。
遥控小车可以接受下列三条指令之一：
"G"：直走 1 个单位
"L"：左转 90 度
"R"：右转 90 度
给定一批指令，遥控小车按顺序执行每个指令后，请计算遥控小车最终所处的位置。
> 用例保证整个过程中坐标(x,y)的值都在 int (32 位系统)范围内 字符串表示的一批遥控指令，仅由字符 G、L、R组成，长度范围[1,100]*/

#include <stdio.h>
#include <string.h>

void ExecCommand(char *commands, char *output, int outputSize)
{
    // 初始化
    int x = 0, y = 0;
    int dir = 0;    // 0: 北 1: 东 2: 南 3: 西

    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};

    for (int i = 0; commands[i] != '\0'; ++i) {
        char cmd = commands[i];
        if (cmd == 'G')
        {
            x += dx[dir];
            y += dy[dir];
        }
        else if (cmd == 'L')
        {
            dir = (dir + 3) % 4; // 左转等价于 -1，+3避免负值
        }
        else if (cmd == 'R')
        {
            dir = (dir + 1) % 4;
        }
    }

    // 输出格式为 "(x,y)"
    snprintf(output, outputSize, "(%d,%d)", x, y);
}