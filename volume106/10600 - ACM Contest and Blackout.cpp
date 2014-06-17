#include <stdio.h>
#include <algorithm>
using namespace std;
struct edg {
    int x, y, v, enable;
};
edg E[10005];
bool cmp(edg a, edg b) {
    return a.v < b.v;
}
int P[105], R[105];
void init(int n) {
    static int i;
    for(int i = 0; i <= n; i++)
        P[i] = i, R[i] = 1;
}
int findp(int x) {
    return x == P[x] ? x : P[x]=findp(P[x]);
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x != y) {
        if(R[x] > R[y])
            R[x] += R[y], P[y] = x;
        else
            R[y] += R[x], P[x] = y;
        return 1;
    }
    return 0;
}
int main() {
    int t, n, m, x, y, v;
    int i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &x, &y, &v);
            E[i].x = x, E[i].y = y, E[i].v = v;
            E[i].enable = 0;
        }
        sort(E, E+m, cmp);
        int cost = 0, ontree[n+1], idx = 0;
        init(n);
        for(i = 0; i < m; i++) {
            if(joint(E[i].x, E[i].y)) {
                cost += E[i].v;
                ontree[idx++] = i;
            }
        }
        printf("%d ", cost);
        int mincost = 0xfffffff;
        for(i = 0; i < idx; i++) {
            cost = 0;
            E[ontree[i]].enable = 1;
            init(n);
            int cnt = 0;
            for(j = 0; j < m; j++) {
                if(!E[j].enable && joint(E[j].x, E[j].y)) {
                    cost += E[j].v;
                    cnt++;
                }
            }
            E[ontree[i]].enable = 0;
            if(mincost > cost && cnt == n-1) // cnt important
                mincost = cost;
        }
        printf("%d\n", mincost);
    }
    return 0;
}
