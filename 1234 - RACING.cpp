#include <stdio.h>
struct edge {
    int x, y, v;
};
edge D[100000], E[100000];
void sort(int n) {
    int w[1001] = {}, i;
    for(i = 0; i < n; i++)
        w[D[i].v]++;
    for(i = 999; i >= 0; i--)
        w[i] += w[i+1];
    for(i = 0; i < n; i++) {
        E[--w[D[i].v]] = D[i];
    }
}
int p[10001], r[10001];
void init(int n) {
    int i;
    for(i = 0; i <= n; i++)
        p[i] = i, r[i] = 1;
}
int find(int x) {
    return p[x] == x ? x : (p[x]=find(p[x]));
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
int main() {
    int t, n, m, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        int sum = 0;
        for(i = 0; i < m; i++) {
            scanf("%d %d %d", &D[i].x, &D[i].y, &D[i].v);
            sum += D[i].v;
        }
        sort(m);
        init(n);
        for(i = 0; i < m; i++) {
            if(joint(E[i].x, E[i].y))
                sum -= E[i].v;
        }
        printf("%d\n", sum);
    }
    scanf("%d", &t);
    return 0;
}
