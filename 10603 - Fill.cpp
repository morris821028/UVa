#include <stdio.h>
#define min(x, y) ((x) < (y) ? (x) : (y))
#define oo 0xfffffff
int A, B, C, D, JUG[3];
int dp[201][201][201], res[201];
void dfs(int a, int b, int c, int tot) {
    if(tot >= res[D])   return;
    if(tot >= dp[a][b][c])  return;
    dp[a][b][c] = tot;
    res[a] = min(res[a], tot);
    res[b] = min(res[b], tot);
    res[c] = min(res[c], tot);
    if(a < B-b) dfs(0, b+a, c, tot+a);
    else        dfs(a-(B-b), B, c, tot+(B-b));
    if(a < C-c) dfs(0, b, c+a, tot+a);
    else        dfs(a-(C-c), b, C, tot+(C-c));
    if(b < A-a) dfs(a+b, 0, c, tot+b);
    else        dfs(A, b-(A-a), c, tot+(A-a));
    if(b < C-c) dfs(a, 0, c+b, tot+b);
    else        dfs(a, b-(C-c), C, tot+(C-c));
    if(c < A-a) dfs(a+c, b, 0, tot+c);
    else        dfs(A, b, c-(A-a), tot+(A-a));
    if(c < B-b) dfs(a, b+c, 0, tot+c);
    else        dfs(a, B, c-(B-b), tot+(B-b));

}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int i, j, k;
        scanf("%d %d %d %d", &A, &B, &C, &D);
        for(i = 0; i <= A; i++)
            for(j = 0; j <= B; j++)
                for(k = 0; k <= C; k++)
                    dp[i][j][k] = oo;
        JUG[0] = A, JUG[1] = B, JUG[2] = C;
        for(i = 0; i <= D; i++)
            res[i] = oo;
        dfs(0, 0, C, 0);
        while(res[D] == oo) D--;
        printf("%d %d\n", res[D], D);
    }
    return 0;
}
