#include <stdio.h>
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
    }
}
int main() {
    int n, m, q, a, b;
    while(scanf("%d %d %d", &n, &m, &q) == 3) {
        init(n);
        while(m--) {
            scanf("%d %d", &a, &b);
            joint(a, b);
        }
        while(q--) {
            scanf("%d %d", &a, &b);
            if(find(a) == find(b))
                puts(":)");
            else
                puts(":(");
        }
    }
    return 0;
}
