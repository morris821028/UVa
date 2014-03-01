#include <stdio.h>
#include <vector>
#define maxN 32768
using namespace std;
typedef struct {
    int nd, dp;
} ELE;
vector<int> g[maxN];
int lidx[maxN], tidx, M;
ELE tree[maxN<<2], stk[maxN<<1];
void dfs(int nd, int dep) {
    if(!lidx[nd])
        lidx[nd] = tidx;
    stk[tidx].nd = nd, stk[tidx++].dp = dep;
    for(vector<int>::iterator it = g[nd].begin();
        it != g[nd].end(); it++) {
        dfs(*it, dep+1);
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
int ReadInt(int *x) {
    static char c, neg;
    while((c = getchar()) < '-')    {if(c == EOF) return EOF;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = getchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
int main() {
    int n, q, x, i, j;
    while(scanf("%d %d", &n, &q) == 2) {
        for(i = 1; i <= n; i++) {
            g[i].clear();
            lidx[i] = 0;
            while(ReadInt(&x), x)
                g[i].push_back(x);
        }
        tidx = 0;
        dfs(1, 0);
        setTree(tidx);
        ELE ans;
        while(q--) {
            ReadInt(&i), ReadInt(&j);
            i = lidx[i], j = lidx[j];
            if(i > j)
                x = i, i = j, j = x;
            ans = query(i, j);
            printf("%d %d\n", ans.nd, -2*stk[lidx[ans.nd]].dp+stk[i].dp+stk[j].dp);
        }
    }
    return 0;
}
