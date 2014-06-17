#include <stdio.h>
#include <string.h>
int SuDoku[9][9], row[9][10], column[9][10], grid[9][10];
int n, tn, flag;
void DFS(int now) {
    if(flag == 1)
        return ;
    if(now == n*n) {
        int i, j;
        flag = 1;
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(j)
                    printf(" ");
                printf("%d", SuDoku[i][j]);
            }
            puts("");
        }
    }
    int x = now/n, y = now%n;
    if(SuDoku[x][y] != 0)
        DFS(now+1);
    else {
        int i, g = x/tn*tn+y/tn;
        for(i = 1; i <= n; i++) {
            if(row[x][i] == 0 && column[y][i] == 0 && grid[g][i] == 0) {
                row[x][i] = 1;
                column[y][i] = 1;
                grid[g][i] = 1;
                SuDoku[x][y] = i;
                DFS(now+1);
                SuDoku[x][y] = 0;
                row[x][i] = 0;
                column[y][i] = 0;
                grid[g][i] = 0;
            }
        }
    }
}
int main() {
    int first = 1, i, j;
    while(scanf("%d", &n) == 1) {
        tn = n;
        n = n*n;
        memset(row, 0, sizeof(row));
        memset(column, 0, sizeof(column));
        memset(grid, 0, sizeof(grid));
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                scanf("%d", &SuDoku[i][j]);
                row[i][SuDoku[i][j]] = 1;
                column[j][SuDoku[i][j]] = 1;
                grid[i/tn*tn+j/tn][SuDoku[i][j]] = 1;
            }
        }
        if(!first)
            puts("");
        flag = 0;
        DFS(0);
        if(!flag)
            puts("NO SOLUTION");
        first = 0;
    }
    return 0;
}
