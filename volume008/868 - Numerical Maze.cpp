#include <bits/stdc++.h>
using namespace std;

int n, m;
int used[105][105] = {}, g[105][105];
int ry, flag;
void dfs(int x, int y, int p, int q) {
    if(x >= n || x < 0 || y >= m || y < 0)
        return;
    if(g[x][y] != p)
		return;
    if(used[x][y])  
		return;
    if (x == n-1) {
        if (y < ry)	ry = y;
        flag = 1;
        return;
    }
    if(p == q)	p = 0, q++;
    used[x][y] = 1;
    dfs(x, y+1, p+1, q);
    dfs(x, y-1, p+1, q);
    dfs(x+1, y, p+1, q);
    dfs(x-1, y, p+1, q);
    used[x][y] = 0;
}
int main() {
	int testcase;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                scanf("%d", &g[i][j]);
        int ly = -1;
        for (int i = 0; i < m; i++) {
            flag = 0, ry = INT_MAX, ly = i;
            dfs(0, i, 1, 1);
            if (flag)	break;
        }
        printf("%d %d\n%d %d\n", 1, ly+1, n, ry+1);
        if (testcase)
        	puts("");
    }
    return 0;
}
/*
1

5 5
3 1 1 1 2
1 2 1 1 2
2 1 3 4 1
3 1 2 1 2
3 1 3 2 3
*/
