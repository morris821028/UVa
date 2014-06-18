#include <stdio.h>

int main() {
    int t, i, j;
    int n, m;
    char ch[1000][500][2];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(i = 0; i < n; i++) {
            for(j = 0; j < m; j++)
                scanf("%s", ch[i][j]);
        }
        int p[1000] = {};
        for(i = 0; i < m; i++) {
            int Y = 0, N = 0;
            for(j = 0; j < n; j++)
                if(p[j] == 0) {
                    if(ch[j][i][0] == 'Y')
                        Y++;
                    else
                        N++;
                }
            if(N == 0)  N = 0xfffff;
            if(Y == 0)  Y = 0xfffff;
            if(Y > N) {
                for(j = 0; j < n; j++) {
                    if(p[j] == 0 && ch[j][i][0] == 'Y')
                        p[j] = 1;
                }
            } else if(Y < N) {
                for(j = 0; j < n; j++) {
                    if(p[j] == 0 && ch[j][i][0] == 'N')
                        p[j] = 1;
                }
            }
        }
        int at = -1, ans[1000] = {};
        for(i = 0; i < n; i++)
            if(p[i] == 0)
                ans[++at] = i;
        if(at >= 0) {
            printf("%d", ans[0]+1);
            for(i = 1; i <= at; i++)
                printf(" %d", ans[i]+1);
            puts("");
        } else {
            puts("");
        }
    }
    return 0;
}
