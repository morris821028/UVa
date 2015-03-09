#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <math.h>
using namespace std;
struct ele {
    int x, y, v;
};
bool cmp (ele a, ele b) {
    return a.v < b.v;
}
int P[1000];
void init(int n) {
    for(int i = 0; i <= n; i++)
        P[i] = i;
}
int findp(int x) {
    return P[x] == x ? x : (P[x]=findp(P[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x != y) {
        P[x] = y;
        return 1;
    }
    return 0;
}
int main() {
    int n, p, q;
    int i, j, x[105], y[105];
    while(scanf("%d", &n) == 1 && n) {
        scanf("%d %d", &p, &q);
        for(i = 1; i <= n; i++) {
            scanf("%d %d", &x[i], &y[i]);
        }
        ele e, A[10005];
        int m = 0;
        for(i = 1; i <= n; i++) {
            for(j = i+1; j <= n; j++) {
                e.x = i, e.y = j;
                e.v = (x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]);
                A[m] = e;
                m++;
            }
        }
        sort(A, A+m, cmp);
        init(n);
        joint(p, q);
        double ans = 0;
        ans = sqrt((x[p]-x[q])*(x[p]-x[q])+(y[p]-y[q])*(y[p]-y[q]));
        for(i = 0; i < m; i++) {
            if(joint(A[i].x, A[i].y)) {
                ans += sqrt(A[i].v);
            }
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}
