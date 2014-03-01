#include <stdio.h>

int main() {
    int t, x, y, i, j, test = 0;
    char cmd[2000];
    scanf("%d", &t);
    while(t--) {
        int map[32][32] = {};
        scanf("%d %d", &x, &y);
        scanf("%s", cmd);
        for(i = 0; cmd[i]; i++) {
            if(cmd[i] == 'E') {
                map[x][y-1] = 1;
                x++;
            }
            if(cmd[i] == 'N') {
                map[x][y] = 1;
                y++;
            }
            if(cmd[i] == 'W') {
                map[x-1][y] = 1;
                x--;
            }
            if(cmd[i] == 'S') {
                map[x-1][y-1] = 1;
                y--;
            }
        }
        printf("Bitmap #%d\n", ++test);
        for(i = 31; i >= 0; i--) {
            for(j = 0; j < 32; j++) {
                putchar(map[j][i] ? 'X' : '.');
            }
            puts("");
        }
        puts("");
    }
    return 0;
}
