#include <stdio.h>
#include <string.h>

int map[51][51], deg[51];
int p[51], r[51];
void init() {
    int i;
    for(i = 0; i <= 50; i++) {
        p[i] = i, r[i] = 1;
    }
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
void dfs(int node) {
    int i;
    for(i = 1; i <= 50; i++) {
        if(map[node][i]) {
            map[node][i]--;
            map[i][node]--;
            dfs(i);
            printf("%d %d\n", i, node);
        }
    }
}
int main() {
    int t, test = 0, n, x, y, i;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        memset(map, 0, sizeof(map));
        memset(deg, 0, sizeof(deg));
        init();
        while(n--) {
            scanf("%d %d", &x, &y);
            map[x][y]++;
            map[y][x]++;
            deg[x]++, deg[y]++;
            joint(x, y);
        }
        printf("Case #%d\n", ++test);
        int st, flag = 0;
        for(i = 1; i <= 50; i++) {
            if(deg[i]) {
                st = i;
                if(deg[i]&1)
                    flag = 1;
            }
        }
        for(i = 1; i <= 50; i++) {
            if(deg[i]) {
                if(find(st) != find(i))
                    flag = 1;
            }
        }
        if(flag)
            puts("some beads may be lost");
        else
            dfs(st);
        if(t)
            puts("");
    }
    return 0;
}
