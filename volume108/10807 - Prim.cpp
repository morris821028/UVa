#include <stdio.h>
#include <algorithm>
#include <string.h>
using namespace std;
struct edge {
    int x, y, v;
    bool operator<(const edge &a) const {
        return v < a.v;
    }
};
edge E[105];
int ret = 0xfffffff;
int n, m;
int findp(int x, int p[]) {
    return (x == p[x]) ? x : (p[x]=findp(p[x],p));
}
int joint(int x, int y, int p[]) {
    x = findp(x, p), y = findp(y, p);
    if(x == y)
        return 0;
    p[x] = y;
    return 1;
}
int runtime = 0;
void dfs(int idx, int costA, int costB, int cntA, int cntB, int pA[], int pB[]) {
    if(cntA == n-1 && cntB == n-1) {
        ret = min(ret, costA+costB);
        return;
    }
    if(runtime > 500000)
        return;
    runtime++;
    if(idx == m)    return;
    if(costA+costB+(n-1-cntA+n-1-cntB)*(E[idx].v) >= ret || (n-1-cntA+n-1-cntB) > m-idx)
        return;
    int ppA[11], ppB[11], tcostA = costA, tcostB = costB, tcntA = cntA, tcntB = cntB;
    if(cntA != n-1) {
        memcpy(ppA, pA, sizeof(ppA));
        memcpy(ppB, pB, sizeof(ppB));
        if(joint(E[idx].x, E[idx].y, ppA)) {
            tcntA = cntA+1;
            tcostA = costA + E[idx].v;
        }
        dfs(idx+1, tcostA, costB, tcntA, cntB, ppA, ppB);
    }
    memcpy(ppA, pA, sizeof(ppA));
    memcpy(ppB, pB, sizeof(ppB));
    tcostA = costA, tcostB = costB, tcntA = cntA, tcntB = cntB;
    if(joint(E[idx].x, E[idx].y, ppB)) {
        tcntB = cntB+1;
        tcostB = costB + E[idx].v;
    }
    dfs(idx+1, costA, tcostB, cntA, tcntB, ppA, ppB);
}
int main() {
    while(scanf("%d %d", &n, &m) == 2 && n) {
        ret = 1;
        runtime = 0;
        int tot;
        int i;
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &E[i].x, &E[i].y, &E[i].v);
            ret += E[i].v;
        }
        sort(E, E+m);
        tot = ret-1;
        int pA[11], pB[11];
        for(i = 1; i <= n; i++)
            pA[i] = i, pB[i] = i;
        dfs(0,0,0,0,0, pA, pB);
        if(ret == tot+1)
            puts("No way!");
        else
            printf("%d\n", ret);
    }
    return 0;
}
