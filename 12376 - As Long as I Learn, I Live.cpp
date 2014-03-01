#include <stdio.h>

int main() {
    int t, cases = 0, v[105];
    int g[105][105], gt[105];
    int i, j, n, m, x, y;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++)
            scanf("%d", &v[i]), gt[i] = 0;
        while(m--) {
            scanf("%d %d", &x, &y);
            g[x][gt[x]++] = y;
        }
        int nd = 0, learn = 0, w;
        while(true) {
            learn += v[nd];
            w = 0;
            for(i = 0; i < gt[nd]; i++) {
                if(v[g[nd][i]] > w)
                    j = g[nd][i], w = v[j];
            }
            if(w == 0) break;
            nd = j;
        }
        printf("Case %d: %d %d\n", ++cases, learn, nd);
    }
    return 0;
}
