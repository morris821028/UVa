#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
int g[105][105], used[105][105];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int n, m;
char ret[105][105];
void dfs(int x, int y, int px, int py) {
    if(x < 0 || y < 0 || x >= n || y >= m)
        return;
    if(used[x][y])
        return;
    used[x][y] = 1;
    if(px >= 0) {
        ret[((x*2+1)+(px*2+1))/2][((y*2+1)+(py*2+1))/2] = '.';
    }
    ret[x*2+1][y*2+1] = '.';
    int cnt = 0, dir = 0;
    if(x == n-1 && y == m-1)    return;
    while(cnt < 10) {
        dir = rand()%4;
        dfs(x+dx[dir], y+dy[dir], x, y);
        cnt++;
    }
}
int main() {
    srand (time(NULL));
    while(scanf("%d %d", &n, &m) == 2) {
        memset(g, 0, sizeof(g));
        memset(used, 0, sizeof(used));
        memset(ret, '#', sizeof(ret));
        dfs(0,0, -1,-1);
        int i, j;
        for(i = 0; i <= 2*n; i++) {
            for(j = 0; j <= 2*m; j++) {
                printf("%c", ret[i][j]);
            }
            puts("");
        }
    }
    return 0;
}
