#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct edge {
    int x, y, v;
};
int p[751], r[751];
void init(int n) {
    for(int i= 0; i <= n; i++)
        p[i] = i, r[i] = 1;
}
int find(int x) {
    return x == p[x] ? x : (p[x]=find(p[x]));
}
int joint(int x, int y) {
    x = find(x), y = find(y);
    if(x != y) {
        if(r[x] > r[y])
            r[x] += r[y], p[y] = x;
        else
            r[y] += r[x], p[x] = y;
        return 1;
    }
    return 0;
}
int cmp(const void *i, const void *j) {
    static edge *a, *b;
    a = (edge *)i, b = (edge *)j;
    return a->v - b->v;
}
edge D[500000];
int main() {
    int n, m, i, j;
    int x[750], y[750];
    while(scanf("%d", &n) == 1) {
        init(n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", x+i, y+i);
        }
        scanf("%d", &m);
        int connect = 0;
        while(m--) {
            scanf("%d %d", &i, &j);
            i--, j--;
            connect += joint(i, j);
        }
        m = 0;
        for(i = 0; i < n; i++) {
            for(j = i+1; j < n; j++) {
                if(find(i) != find(j)) {
                    D[m].x = i, D[m].y = j;
                    D[m].v = (x[i]-x[j])*(x[i]-x[j])+
                        (y[i]-y[j])*(y[i]-y[j]);
                    m++;
                }
            }
        }
        qsort(D, m, sizeof(edge), cmp);
        double ans = 0;
        for(i = 0; i < m; i++) {
            if(joint(D[i].x, D[i].y)) {
                ans += sqrt(D[i].v);
                connect++;
                if(connect == n-1)
                    break;
            }
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}
