#include <stdio.h>

int main() {
    int S, N;
    while(scanf("%d %d", &S, &N) == 2 && S) {
        int ans = -1, aset[20], an;
        int n, s[20], i, j, k;
        for(i = 0; i < N; i++) {
            scanf("%d", &n);
            for(j = 0; j < n; j++)
                scanf("%d", &s[j]);
            int dp[1005] = {};
            dp[0] = 1;
            for(j = 0; j < n; j++) {
                for(k = 0; k <= 1000; k++) {
                    if(dp[k] && dp[k] <= S) {
                        if(dp[k+s[j]] > dp[k]+1 || dp[k+s[j]] == 0)
                            dp[k+s[j]] = dp[k]+1;
                    }
                }
            }
            j = 0;
            while(dp[j]) j++;
            j--;
            if(j > ans) {
                ans = j, an = n;
                for(j = 0; j < n; j++)
                    aset[j] = s[j];
            } else if(ans == j) {
                if(an > n) {
                    an = n;
                    for(j = 0; j < n; j++)
                        aset[j] = s[j];
                } else if(an == n) {
                    int flag = 0;
                    for(j = n-1; j >= 0; j--)
                        if(aset[j] > s[j]) {
                            flag = 0;
                            break;
                        } else if(aset[j] < s[j]) {
                            flag = 1;
                            break;
                        }
                    if(!flag)
                        for(j = 0; j < n; j++)
                            aset[j] = s[j];

                }
            }
        }
        printf("max coverage =%4d :", ans);
        for(i = 0; i < an; i++)
            printf("%3d", aset[i]);
        puts("");
    }
    return 0;
}
