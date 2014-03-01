#include <stdio.h>
#include <string.h>
int n;
char map[30][30], used[30][30];
void color(int x, int y) {
    if(x < 0 || x >= n || y < 0 || y >= n)
        return ;
    if(used[x][y] != 0 || map[x][y] == '0')
        return;
    used[x][y] = 1;
    int i, j;
    for(i = -1; i <= 1; i++)
        for(j = -1; j <= 1; j++)
            color(x+i, y+j);
}
int main() {
    int img = 0, i, j;
    while(scanf("%d", &n) == 1) {
        for(i = 0; i < n; i++) {
            scanf("%s", map[i]);
        }
        memset(used, 0, sizeof(used));
        int cnt = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(map[i][j] == '1' && used[i][j] == 0) {
                    color(i, j);
                    cnt++;
                }
            }
        }
        printf("Image number %d contains %d war eagles.\n", ++img, cnt);
    }
    return 0;
}
