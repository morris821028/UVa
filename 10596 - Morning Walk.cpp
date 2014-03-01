#include <stdio.h>
int p[201], r[201];
int find(int x) {
    return p[x] == x ? x : p[x]=find(p[x]);
}
void joint(int x, int y) {
    x = find(x), y = find(y);
    if(x != y) {
        if(r[x] > r[y])
            r[x] += r[y], p[y] = x;
        else
            r[y] += r[x], p[x] = y;
    }
}
int main() {
    int n, m, x, y;
    while(scanf("%d %d", &n, &m) == 2) {
        int i, j, deg[n];
        for(i = 0; i < n; i++)
            r[i] = 1, p[i] = i, deg[i] = 0;
        while(m--) {
            scanf("%d %d", &x, &y);
            joint(x, y);
            deg[x]++, deg[y]++;
        }
        int flag = 0;
        for(i = 0; i < n; i++) {
            if(deg[i]&1) {
                flag = 1;
            }
        }
        if(r[find(0)] != n)
            flag = 1;
        if(flag)
            puts("Not Possible");
        else
            puts("Possible");
    }
    return 0;
}
