#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct E {
    int x, y;
    int v;
};
E D[250000];
int cmp(const void *i, const void *j) {
    E *a, *b;
    a = (E *)i, b = (E *)j;
    return a->v - b->v;
}
int p[501], r[501];
void init(int n) {
    int i;
    for(i = 0; i <= n; i++)
        p[i] = i, r[i] = 1;
}
int find(int x) {
    return p[x] == x ? x : (p[x] = find(p[x]));
}
int joint(int x, int y) {
    x = find(x), y = find(y);
    if(x != y) {
        if(r[x] > r[y])
            p[y] = x, r[x] += r[y];
        else
            p[x] = y, r[y] += r[x];
        return 1;
    }
    return 0;
}
int main() {
    int t, S, P;
    int x[501], y[501], i, j;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &S, &P);
        int m = 0;
        for(i = 0; i < P; i++) {
            scanf("%d %d", &x[i], &y[i]);
            for(j = i-1; j >= 0; j--) {
                D[m].x = i, D[m].y = j;
                D[m].v = (x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]);
                m++;
            }
        }
        qsort(D, m, sizeof(E), cmp);
        init(P);
        int cnt = 0;
        for(i = 0; i < m; i++) {
            cnt += joint(D[i].x, D[i].y);
            if(cnt == P-S) {
                printf("%.2lf\n", sqrt(D[i].v));
                break;
            }
        }
    }
    return 0;
}
