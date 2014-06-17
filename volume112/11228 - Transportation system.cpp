#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct {
    int i, j, v;
} E;
E D[1000000];
int R[1005], P[1005];
int cmp(const void *i, const void *j) {
    static E *a, *b;
    a = (E *)i, b = (E *)j;
    return a->v - b->v;
}
void init(int n) {
    int i;
    for(i = 0; i < n; i++)
        R[i] = 1, P[i] = i;
}
int findp(int x) {
    return P[x] == x ? x : P[x]=findp(P[x]);
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
    int t, n, m, r, i, j, cases = 0;
    int x[1005], y[1005];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &r);
        for(i = 0; i < n; i++)
            scanf("%d %d", &x[i], &y[i]);
        init(n);
        m = 0;
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                D[m].i = i, D[m].j = j;
                D[m].v = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
                m++;
            }
        }
        qsort(D, m, sizeof(E), cmp);
        int ac = 0, state = 1;
        double road = 0, rail = 0;
        r = r*r;
        for(i = 0; i < m; i++) {
            if(joint(D[i].i, D[i].j)) {
                if(D[i].v > r) {
                    rail += sqrt(D[i].v), state ++;
                } else {
                    road += sqrt(D[i].v);
                }
                ac++;
                if(ac == n-1)   break;
            }
        }
        printf("Case #%d: %d %.lf %.lf\n", ++cases, state, road, rail);
    }
    return 0;
}
