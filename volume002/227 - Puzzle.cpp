#include <stdio.h>
#include <string.h>
int main() {
    char map[5][6], cmd;
    int cases = 0;
    while(gets(map[0])) {
        if(!strcmp(map[0], "Z"))
            break;
        if(cases)
            puts("");
        printf("Puzzle #%d:\n", ++cases);
        gets(map[1]), gets(map[2]), gets(map[3]), gets(map[4]);
        int i, j, x, y;
        for(i = 0; i < 5; i++) {
            for(j = 0; j < 5; j++) {
                if(map[i][j] == ' ' || map[i][j] == '\0')
                    x = i, y = j;
            }
        }
        int error = 0;
        while(1) {
            cmd = getchar();
            if(cmd == 'A') {
                if(x == 0) {
                    error = 1;
                    break;
                }
                map[x][y] = map[x-1][y];
                x--;
            } else if(cmd == 'B') {
                if(x == 4) {
                    error = 1;
                    break;
                }
                map[x][y] = map[x+1][y];
                x++;
            } else if(cmd == 'L') {
                if(y == 0) {
                    error = 1;
                    break;
                }
                map[x][y] = map[x][y-1];
                y--;
            } else if(cmd == 'R') {
                if(y == 4) {
                    error = 1;
                    break;
                }
                map[x][y] = map[x][y+1];
                y++;
            } else if(cmd == '0')
                break;
        }
        if(cmd != '0') {
            while((cmd = getchar()) != '0');
        }
        while((cmd = getchar()) != '\n');
        if(error)
            puts("This puzzle has no final configuration.");
        else {
            map[x][y] = ' ';
            for(i = 0; i < 5; i++) {
                for(j = 0; j < 5; j++) {
                    if(j)
                        putchar(' ');
                    putchar(map[i][j]);
                }
                puts("");
            }
        }
        memset(map, 0, sizeof(map));
    }
    return 0;
}
