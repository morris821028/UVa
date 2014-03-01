#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define N 155
int g[N][N];//memset(g, 0, sizeof(g));
int StoerWagner(int n) {//1...n
    int i, j;
    int ret = 0xfffffff;
    int v[N], w[N], vis[N];
    for(i = 1; i <= n; i++)
        v[i] = i;
    while(n > 1) {
        int mxp = 1, prev = 2;
        for(i = 1; i <= n; i++) {
            w[v[i]] = g[v[1]][v[i]];
            if(w[v[i]] > w[v[mxp]])
                mxp = i;
        }
        memset(vis, 0, sizeof(vis));
        vis[v[1]] = 1;
        for(i = 1; i < n; i++) {
            if(i == n-1) {
                ret = min(ret, w[v[mxp]]);
                for(j = 1; j <= n; j++) {
                    g[v[prev]][v[j]] += g[v[j]][v[mxp]];
                    g[v[j]][v[prev]] = g[v[prev]][v[j]];
                }
                v[mxp] = v[--n];
            }
            vis[v[mxp]] = 1;
            prev = mxp, mxp = -1;
            for(j = 1; j <= n; j++) {
                if(!vis[v[j]]) {
                    w[v[j]] += g[v[prev]][v[j]];
                    if(mxp == -1 || w[v[mxp]] < w[v[j]])
                        mxp = j;
                }
            }
            printf("%d\n", mxp);
        }
    }
    return ret;
}
int main() {
    int testcase, n, m, x, y, c;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%d %d", &n, &m);
        memset(g, 0, sizeof(g));
        while(m--) {
            scanf("%d %d %d", &x, &y, &c);
            g[x][y] += c;
            g[y][x] += c;
        }
        printf("%d\n", StoerWagner(n));
    }
    return 0;
}
