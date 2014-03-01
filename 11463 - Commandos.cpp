#include <stdio.h>
#define min(x, y) ((x)<(y)?(x):(y))
#define max(x, y) ((x)>(y)?(x):(y))
int main() {
    int t, cases = 0;
    scanf("%d", &t);
    while(t--) {
        int n, m, i, j, k;
        scanf("%d %d", &n, &m);
        int f[101][101] = {};
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                if(i != j)
                    f[i][j] = 0xffff;
        while(m--) {
            scanf("%d %d", &i, &j);
            f[i][j] = 1;
            f[j][i] = 1;
        }
        int st, ed;
        scanf("%d %d", &st, &ed);
        for(k = 0; k < n; k++)
            for(i = 0; i < n; i++)
                for(j = 0; j < n; j++)
                    f[i][j] = min(f[i][k]+f[k][j], f[i][j]);
        int ans = 0;
        for(i = 0; i < n; i++)
            ans = max(ans, f[st][i]+f[i][ed]);
        printf("Case %d: %d\n", ++cases, ans);
    }
    return 0;
}
