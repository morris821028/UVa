#include <stdio.h>
#include <vector>
#define maxN 65536
using namespace std;
typedef struct {
    int nd, dp;
} ELE;
vector<int> g[maxN];
int lidx[maxN], tidx, M;
ELE tree[maxN<<2], stk[maxN<<1];
void dfs(int nd, int dep, int p) {
    if(!lidx[nd])
        lidx[nd] = tidx;
    stk[tidx].nd = nd, stk[tidx++].dp = dep;
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        if(*it == p)    continue;
        dfs(*it, dep+1, nd);
        stk[tidx].nd = nd, stk[tidx++].dp = dep;
    }
}
void setTree(int n) {
    for(M = 1; M < n+1; M <<= 1);
    for(int i = 2*M-1; i > 0; i--) {
        if(i >= M)
            tree[i] = stk[i-M];
        else {
            if(tree[i<<1].dp < tree[i<<1|1].dp)
                tree[i] = tree[i<<1];
            else
                tree[i] = tree[i<<1|1];
        }
    }
}
ELE query(int s, int t) {
    static int i;
    ELE ans;
    ans.dp = 0xfffff;
    for(s = s+M-1, t = t+M+1; (s^t) != 1;) {
        if(~s&1) {
            if(ans.dp > tree[s^1].dp)
                ans = tree[s^1];
        }
        if(t&1) {
            if(ans.dp > tree[t^1].dp)
                ans = tree[t^1];
        }
        s >>= 1, t >>= 1;
    }
    return ans;
}
int main() {
    int n, m, q, x, i, j;
    int x1, y1, x2, y2;
    char mg[255][255] = {};
    int gn[255][255] = {};
    while(scanf("%d %d %d", &n, &m, &q) == 3) {
        int size = 0;
        for(i = 0; i < n; i++) {
            scanf("%s", mg[i]);
            for(j = 0; j < m; j++) {
                if(mg[i][j] == '.')
                    gn[i][j] = ++size;
            }
        }
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++) {
                if(mg[i][j] != '.')
                    continue;
                if(mg[i+1][j] == '.')
                    g[gn[i][j]].push_back(gn[i+1][j]);
                if(mg[i-1][j] == '.')
                    g[gn[i][j]].push_back(gn[i-1][j]);
                if(mg[i][j+1] == '.')
                    g[gn[i][j]].push_back(gn[i][j+1]);
                if(mg[i][j-1] == '.')
                    g[gn[i][j]].push_back(gn[i][j-1]);
            }
        }
        tidx = 0;
        dfs(1, 0, -1);
        setTree(tidx);
        ELE ans;
        int sum = 0;
        while(q--) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            i = lidx[gn[x1][y1]], j = lidx[gn[x2][y2]];
            if(i > j)
                x = i, i = j, j = x;
            ans = query(i, j);
            sum += -2*stk[lidx[ans.nd]].dp+stk[i].dp+stk[j].dp;
        }
        printf("%d\n", sum);
        for(i = 0; i <= size; i++)
            g[i].clear();
    }
    return 0;
}
