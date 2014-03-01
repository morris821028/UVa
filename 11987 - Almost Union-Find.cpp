#include <stdio.h>

int p[200001], r[200001], mapped[200001];
long long s[200001];
void init(int n) {
    static int i;
    for(i = 0; i <= n; i++) {
        p[i] = i, s[i] = 0, r[i] = 1;
        mapped[i] = i;
    }
}
int find(int x) {
    return p[x] == x ? x : p[x]=find(p[x]);
}
void joint(int x, int y, int i, int j) {
    if(x == y)
        return;
    s[x] += s[y];
    r[x] += r[y];
    s[y] = 0;
    r[y] = 0;
    p[y] = x;
}
int main() {
    int n, m, op, i, j, t, x, y;
    while(scanf("%d %d", &n, &m) == 2) {
        init(n+m);
        for(i = 0; i <= n; i++)
            s[i] = i;
        while(m--) {
            scanf("%d %d", &op, &i);
            if(op == 3) {
                t = find(mapped[i]);
                printf("%d %lld\n", r[t], s[t]);
            } else if(op == 2) {
                scanf("%d", &j);
                x = find(mapped[i]);
                y = find(mapped[j]);
                if(x != y) {
                    s[x] -= i, r[x]--;
                    mapped[i] = ++n;
                    s[mapped[i]] = i;
                    r[mapped[i]] = 1;
                    joint(find(mapped[i]), find(mapped[j]), i, j);
                }
            } else {
                scanf("%d", &j);
                joint(find(mapped[i]), find(mapped[j]), i, j);
            }
        }
    }
    return 0;
}
