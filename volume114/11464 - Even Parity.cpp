#include <stdio.h>
int ans, g[30][30], n;
void press(int x, int y) {
    g[x][y] = 1-g[x][y];
}
int check(int x, int y) {//is odd
    int cnt = 0;
    if(x-1 >= 0)    cnt += g[x-1][y];
    if(x+1 < n)     cnt += g[x+1][y];
    if(y-1 >= 0)    cnt += g[x][y-1];
    if(y+1 < n)     cnt += g[x][y+1];
    return cnt&1;
}
void dfs(int x, int y, int step) {
    if(step >= ans)
        return;
    if(y == n)
        x++, y = 0;
    if(x == 0) {
        dfs(x, y+1, step);
        if(g[x][y] == 0) {
            press(x, y);
            dfs(x, y+1, step+1);
            press(x, y);
        }
    } else if(x < n) {
        if(check(x-1, y)) {// g[x-1][y] is odd
            if(g[x][y] == 0) {
                press(x, y);
                dfs(x, y+1, step+1);
                press(x, y);
            }
        } else {
            dfs(x, y+1, step);
        }
    } else {
        int i;
        for(i = 0; i < n; i++) {
            if(check(n-1, i))
                return; //is odd
            if(step < ans)
                ans = step;
        }
    }
}
int main() {
    int t, cases = 0;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                scanf("%d", &g[i][j]);
        ans = 0xffff;
        dfs(0,0,0);
        if(ans == 0xffff)
            ans = -1;
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
