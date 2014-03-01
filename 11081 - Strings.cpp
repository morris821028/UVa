#include <stdio.h>
#include <string.h>
int dp[70][70][70], fa[70][70][70], fb[70][70][70];
int main() {
    int t;
    char a[70], b[70], c[70];
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s %s", a+1, b+1, c+1);
        int la, lb, lc;
        int i, j, k;
        la = strlen(a+1);
        lb = strlen(b+1);
        lc = strlen(c+1);
        memset(dp, 0, sizeof(dp));
        memset(fa, 0, sizeof(fa));
        memset(fb, 0, sizeof(fb));
        for(i = 0; i <= la; i++) {
            for(j = 0; j <= lb; j++) {
                dp[0][i][j] = 1;
                fa[0][i][j] = fb[0][i][j] = 1;
            }
        }
        for(i = 0; i <= lc; i++) {
            for(j = 0; j <= la; j++) {
                for(k = 0; k <= lb; k++) {
                    if(j)
                        fa[i][j][k] += fa[i][j-1][k];
                    if(k)
                        fb[i][j][k] += fb[i][j][k-1];
                    if(c[i+1] == a[j+1]) {
                        fa[i+1][j+1][k] += fa[i][j][k];
                        fa[i+1][j+1][k] %= 10007;
                    }
                    if(c[i+1] == b[k+1]) {
                        fb[i+1][j][k+1] += fb[i][j][k];
                        fb[i+1][j][k+1] %= 10007;
                    }
                    dp[i][j][k] = fa[i][j][k] + fb[i][j][k];
                }
            }
        }
        printf("%d\n", dp[lc][la][lb]);
    }
    return 0;
}
