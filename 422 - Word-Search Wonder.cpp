#include <stdio.h>
#include <string.h>
int n, i, j;
int find(char str[], char map[][105]) {
    static int D[][2] = {{0,1},{1,0},{-1,0},{0,-1},
                        {1,1},{1,-1},{-1,1},{-1,-1}};
    int i, j, k, x, y, idx;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(k = 0; k < 8; k++) {
                x = i, y = j, idx = 0;
                while(map[x][y] == str[idx]) {
                    idx++;
                    if(str[idx] == '\0') {
                        printf("%d,%d %d,%d\n", i+1, j+1, x+1, y+1);
                        return 1;
                    }
                    x += D[k][0], y += D[k][1];
                    if(x < 0 || y < 0 || x >= n || y >= n)
                        break;
                }
            }
        }
    }
    return 0;
}
int main() {
    while(scanf("%d", &n) == 1) {
        char map[105][105], str[105];
        for(i = 0; i < n; i++) {
            scanf("%s", &map[i]);
        }
        while(scanf("%s", str) == 1) {
            if(!strcmp(str, "0"))
                break;
            if(!find(str, map))
                puts("Not found");
        }
    }
    return 0;
}
