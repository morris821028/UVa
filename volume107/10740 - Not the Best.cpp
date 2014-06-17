#include <stdio.h>
#include <queue>
#include <vector>
#define oo 0xffffff
using namespace std;
struct arc {
    int to, w;
    arc(int x, int y) : to(x), w(y) {}
};
vector<arc> g[105], invg[105];
int toEDdis[105], fromSTdis[105], used[105], kpath[105];
void prepare(int st, int ed, int k, int n) { // spfa
    int i, tn;
    for(i = 1; i <= n; i++)
        toEDdis[i] = oo, used[i] = 0;
    queue<int> Q;
    toEDdis[ed] = 0;
    Q.push(ed);
    while(!Q.empty()) {
        tn = Q.front();
        Q.pop();
        used[tn] = 0;
        for(i = 0; i < invg[tn].size(); i++) {
            if(toEDdis[invg[tn][i].to] > toEDdis[tn] + invg[tn][i].w) {
                toEDdis[invg[tn][i].to] = toEDdis[tn] + invg[tn][i].w;
                if(!used[invg[tn][i].to]) {
                    used[invg[tn][i].to] = 1;
                    Q.push(invg[tn][i].to);
                }
            }
        }
    }
}
struct cmp {
    bool operator()(arc a, arc b) {
        return a.w > b.w;
    }
};
void sol_kpath(int st, int ed, int k, int n) {
    prepare(st, ed, k, n);
    priority_queue<arc, vector<arc>, cmp> pQ;
    int i;
    arc tn(0,0);
    for(i = 1; i <= n; i++)
        fromSTdis[i] = oo, kpath[i] = 0;
    pQ.push(arc(st, toEDdis[st]));
    while(!pQ.empty()) {
        tn = pQ.top();
        pQ.pop();
        if(kpath[tn.to] >= k)
            continue;
        tn.w -= toEDdis[tn.to];
        kpath[tn.to]++, fromSTdis[tn.to] = tn.w;
        if(kpath[ed] == k) {
            printf("%d\n", fromSTdis[ed]);
            return;
        }
        for(i = 0; i < g[tn.to].size(); i++) {
            pQ.push(arc(g[tn.to][i].to, tn.w+g[tn.to][i].w+toEDdis[g[tn.to][i].to]));
        }
    }
    puts("-1");
}
int main() {
    int n, m, x, y, w, i, st, ed, k;
    while(scanf("%d %d", &n, &m) == 2) {
        if(!n && !m)    break;
        for(i = 1; i <= n; i++)
            g[i].clear(), invg[i].clear();
        scanf("%d %d %d", &st, &ed, &k);
        arc e(0,0);
        while(m--) {
            scanf("%d %d %d", &x, &y, &w);
            e.to = y, e.w = w;
            g[x].push_back(e);
            e.to = x;
            invg[y].push_back(e);
        }
        sol_kpath(st, ed, k, n);
    }
    return 0;
}
