#include <stdio.h>
#include <vector>
#define min(x, y) ((x) < (y) ? (x) : (y))
using namespace std;
int g[1500][100], gt[1500];
int dp[1500][2], used[1500];
void dfs(int nd) {
    used[nd] = 1;
    dp[nd][0] = 0;
    dp[nd][1] = 1;
    int i;
    for(i = gt[nd]-1; i >= 0; i--) {
        if(used[g[nd][i]] == 0) {
            dfs(g[nd][i]);
            dp[nd][0] += dp[g[nd][i]][1];
            dp[nd][1] += min(dp[g[nd][i]][0], dp[g[nd][i]][1]);
        }
    }
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0' && c <= '9')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, i, x, m, y;
    while(ReadInt(&n)) {
        for(i = 0; i < n; i++)
            gt[i] = 0, used[i] = 0;
        for(i = 0; i < n; i++) {
            ReadInt(&x);
            getchar();
            ReadInt(&m);
            while(m--) {
                ReadInt(&y);
                g[x][gt[x]++] = y;
                g[y][gt[y]++] = x;
            }
        }
        if(n == 1)
            puts("1");
        else {
            dfs(1);
            printf("%d\n", min(dp[1][0], dp[1][1]));
        }
    }
    return 0;
}
