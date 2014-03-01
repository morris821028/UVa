#include <stdio.h>
int n, m, way = 0;
int g[65][65], used[65][65];
void dfs(int x, int y, int d) {// 0 up-down, 1 left-right
    if(x == n-1 && y == m-1) {
        way++;
        return;
    }
    used[x][y] = 1;
    if(d == 0) {
        if(x-1 < 0 || used[x-1][y] || g[x-1][y] == 0) {}
        else {
            if(g[x-1][y] == 1)
                dfs(x-1, y, 0);
            else
                dfs(x-1, y, 1);
        }
        if(x+1 >= n || used[x+1][y] || g[x+1][y] == 0) {}
        else {
            if(g[x+1][y] == 1)
                dfs(x+1, y, 0);
            else
                dfs(x+1, y, 1);
        }
    } else {
        if(y-1 < 0 || used[x][y-1] || g[x][y-1] == 0) {}
        else {
            if(g[x][y-1] == 1)
                dfs(x, y-1, 1);
            else
                dfs(x, y-1, 0);
        }
        if(y+1 >= m || used[x][y+1] || g[x][y+1] == 0) {}
        else {
            if(g[x][y+1] == 1)
                dfs(x, y+1, 1);
            else
                dfs(x, y+1, 0);
        }
    }
    used[x][y] = 0;
}
int main() {
    int testcases;
    int i, j, k;
    char s[4][500];
    scanf("%d", &testcases);
    while(testcases--) {
        scanf("%d %d", &n, &m);
        while(getchar() != '\n');
        while(getchar() != '\n');
        for(i = 0; i < n; i++) {
            for(j = 0; j < 4; j++)
                gets(s[j]);
            for(j = 0, k = 1; j < m; j++, k += 4) {
                if(s[1][k] == ' ')
                    g[i][j] = 0;
                else if(s[1][k+2] == '*') // ***
                    g[i][j] = 1;
                else
                    g[i][j] = 2;
            }
        }
        way = 0;
        dfs(0, 0, 0);
        dfs(0, 0, 1);
        printf("Number of solutions: %d\n", way);
    }
    return 0;
}
