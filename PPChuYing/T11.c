void ExecCommand(char *commands, char *output, int outputSize)
{
    int x =0, y = 0;
    int dir = 0;    //0、1、2、3, 北、西、南、东; 要按照顺时针或者逆时针顺序, 要不然不好转向
    int dx[4] = {0, -1, 0, 1};
    int dy[4] = {1, 0, -1, 0};
    for (int i = 0; commands[i] != '\0'; i++) {
        char cmd = commands[i];
        if (cmd == 'G') {
            x += dx[dir];
            y += dy[dir];
        } else if (cmd == 'L'){
            dir = (dir + 1) % 4;
        } else if (cmd == 'R'){
            dir = (dir + 3) % 4;
        }
    }
    snprintf(output, outputSize, "(%d,%d)", x, y);
}