#include <stdio.h>
#include <algorithm>
using namespace std;
int P[755], R[755];
struct edg {
    int x, y, v;
};
edg E[755*755];
bool cmp(edg a, edg b) {
    return a.v < b.v;
}
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
    int t, n, m, x[755], y[755];
    int i, j, a, b;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 1; i <= n; i++)
            scanf("%d %d", &x[i], &y[i]);
        init(n);
        scanf("%d", &m);
        int cnt = 0;
        while(m--) {
            scanf("%d %d", &a, &b);
            cnt += joint(a, b);
        }
        if(cnt == n-1) {
            puts("No new highways need");
        } else {
            m = 0;
            for(i = 1; i <= n; i++) {
                for(j = i+1; j <= n; j++) {
                    E[m].x = i, E[m].y = j;
                    E[m].v = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
                    m++;
                }
            }
            sort(E, E+m, cmp);
            for(i = 0; i < m; i++) {
                if(joint(E[i].x, E[i].y)) {
                    printf("%d %d\n", E[i].x, E[i].y);
                }
            }
        }
        if(t)
            puts("");
    }
    return 0;
}
