#include <stdio.h>
#include <string.h>
short path[1001][1001] = {}, step[1001][1001][3];
int Ca, Cb, N;
int ans, ba, bb;
void dfs(int a, int b, int dp, int cmd, int la, int lb) {
    if(path[a][b] <= dp)
        return ;
    path[a][b] = dp, step[a][b][0] = cmd;
    step[a][b][1] = la, step[a][b][2] = lb;
    if(a == N || b == N) {
        if(dp < ans) {
            ans = dp;
            ba = a, bb = b;
        }
        return ;
    }
    dfs(Ca, b, dp+1, 0, a, b);
    dfs(a, Cb, dp+1, 1, a, b);
    dfs(0, b, dp+1, 2, a, b);
    dfs(a, 0, dp+1, 3, a, b);
    if(a+b <= Cb)        dfs(0, a+b, dp+1, 4, a, b);
    else        dfs(a-(Cb-b), Cb, dp+1, 4, a, b);
    if(a+b <= Ca)        dfs(a+b, 0, dp+1, 5, a, b);
    else        dfs(Ca, b-(Ca-a), dp+1, 5, a, b);

}
void backtracking(int a, int b) {
    if(step[a][b][0] == -1) return;
    backtracking(step[a][b][1], step[a][b][2]);
    switch(step[a][b][0]) {
        case 0:puts("fill A");break;
        case 1:puts("fill B");break;
        case 2:puts("empty A");break;
        case 3:puts("empty B");break;
        case 4:puts("pour A B");break;
        case 5:puts("pour B A");break;
    }
}
int main() {
    while(scanf("%d %d %d", &Ca, &Cb, &N) == 3) {
        memset(path, 63, sizeof(path));
        ans = 0xffff;
        dfs(0, 0, 0, -1, 0, 0);
        backtracking(ba, bb);
        puts("success");
    }
    return 0;
}
