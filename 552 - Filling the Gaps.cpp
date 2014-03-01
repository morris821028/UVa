#include <stdio.h>
#include <string.h>
int main() {
    int n, m;
    while(scanf("%d %d", &n, &m) == 2) {
        char g[20];
        int A[10000] = {}, B[10000] = {};
        int C[65535] = {};
        int noflag = 0, i, j;
        for(i = 0; i < m; i++) {
            scanf("%s", &g);
            for(j = 0; g[j]; j++) {
                if(g[j] != '*') {
                    A[i] |= (g[j]-'0')*(1<<j);
                    B[i] |= 1<<j;
                }
            }
            C[B[i]]++;
            if(C[B[i]] > 1)
                noflag = 1;
        }
        if(noflag) {
            puts("NO");
            continue;
        }
        memset(C, 0, sizeof(C));
        int mask = (1<<n)-1;
        for(i = (1<<n)-1; i >= 0; i--) {
            for(j = 0; j < m; j++) {
                int x = mask^B[j];
                int y = (x&i)|A[j];
                C[y] = 1;
            }
        }
        int ans = 0;
        for(i = (1<<n)-1; i >= 0; i--)
            ans += C[i];
        printf("YES %d\n", ans);
    }
    return 0;
}
