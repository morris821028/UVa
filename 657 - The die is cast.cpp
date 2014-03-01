#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
using namespace std;
char g[105][105];
int dused[105][105], bused[105][105];
int n, m, com;
int dx[] = {0,0,-1,1};
int dy[] = {1,-1,0,0};
void dfs(int x, int y) {
    if(x < 0 || y < 0 || x >= n || y >= m)
        return;
    if(g[x][y] == '.' || dused[x][y])
        return;
    dused[x][y] = 1;
    if(g[x][y] == 'X' && bused[x][y] == 0) {
        queue<int> X, Y;
        X.push(x), Y.push(y);
        bused[x][y] = 1;
        int i, tx, ty;
        while(!X.empty()) {
            x = X.front(), X.pop();
            y = Y.front(), Y.pop();
            for(i = 0; i < 4; i++) {
                tx = x+dx[i], ty = y+dy[i];
                if(tx < 0 || ty < 0 || tx >= n || ty >= m)
                    continue;
                if(g[tx][ty] != 'X' || bused[tx][ty])
                    continue;
                bused[tx][ty] = 1;
                X.push(tx), Y.push(ty);
            }
        }
        com++;
    }
    dfs(x+1, y);
    dfs(x-1, y);
    dfs(x, y+1);
    dfs(x, y-1);
}
int main() {
    int cases = 0;
    int i, j;
    int A[2500], At = 0;
    while(scanf("%d %d", &m, &n) == 2) {
        if(n == 0)
            break;
        for(i = 0; i < n; i++)
            scanf("%s", &g[i]);
        memset(dused, 0, sizeof(dused));
        memset(bused, 0, sizeof(bused));
        At = 0;
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(g[i][j] != '.' && dused[i][j] == 0) {
                    com = 0;
                    dfs(i, j);
                    if(com >= 1 && com <= 6)
                        A[At++] = com;
                }
            }
        }
        printf("Throw %d\n", ++cases);
        sort(A, A+At);
        for(i = 0; i < At; i++) {
            if(i)   putchar(' ');
            printf("%d", A[i]);
        }
        if(At == 0)
            puts("0");
        puts("\n");
    }
    return 0;
}
