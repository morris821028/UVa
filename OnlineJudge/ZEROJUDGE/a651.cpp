#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
vector<int> g[100005];
int ST[530000], label[530000];
int RC[100005][2];
int postOrder[100005], visited[100005], pidx;
void build(int nd) {
    int i;
    RC[nd][0] = pidx;
    for(i = 0; i < g[nd].size(); i++)
        build(g[nd][i]);
    postOrder[pidx] = nd;
    visited[nd] = pidx;
    RC[nd][1] = pidx;
    pidx++;
}
void relax(int k, int l, int r) {
    if(label[k] < 0)    return;
    int m = (l+r)/2;
    ST[k] = min(ST[k], label[k]);
    if(l <= m) {
        if(label[k<<1] < 0)
            label[k<<1] = label[k];
        else
            label[k<<1] = min(label[k], label[k<<1]);
    }
    if(m+1 <= r) {
        if(label[k<<1|1] < 0)
            label[k<<1|1] = label[k];
        else
            label[k<<1|1] = min(label[k], label[k<<1|1]);
    }
    label[k] = -1;
}
int argv;
void modify(int k, int l, int r, int ql, int qr) {
    if(l > r)   return ;
    relax(k, l, r);
    if(ST[k] <= argv)
        return;
    if(l == ql && r == qr) {
        label[k] = argv;
        relax(k, l, r);
        return ;
    }
    int m = (l+r)/2;
    if(m >= qr)
        modify(k<<1, l, m, ql, qr);
    else if(m < ql)
        modify(k<<1|1, m+1, r, ql, qr);
    else {
        modify(k<<1, l, m, ql, m);
        modify(k<<1|1, m+1, r, m+1, qr);
    }
}
int query(int k, int l, int r, int qx) {
    relax(k, l, r);
    if(l == r && l == qx)
        return ST[k];
    int m = (l+r)/2;
    if(qx <= m)
        return query(k<<1, l, m, qx);
    else
        return query(k<<1|1, m+1, r, qx);
}
int main() {
    int T;
    int n, q;
    int i, j, x;
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d", &n, &q);
        for(i = 0; i <= n; i++)
            g[i].clear();
        for(i = 1; i < n; i++) {
            scanf("%d", &x);
            g[x].push_back(i);
        }
        pidx = 0;
        build(0);
        memset(ST, 63, sizeof(ST));
        memset(label, -1, sizeof(label));
        argv = visited[0];
        modify(1, 0, n-1, RC[0][0], RC[0][1]);
        int ans = 0;
        for(i = 1; i <= q; i++) {
            scanf("%d", &x);
            argv = query(1, 0, n-1, visited[x]);
            argv = postOrder[argv];
            ans ^= argv + i;
            //printf("%d %d [%d %d]\n", argv, visited[x], RC[x][0], RC[x][1]);
            argv = visited[x];
            modify(1, 0, n-1, RC[x][0], RC[x][1]);
        }
        printf("%d\n", ans);
    }
    return 0;
}
