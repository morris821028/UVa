#include <stdio.h>

int main() {
    int t, n, i, j, k;
    scanf("%d", &t);
    char f[10000][5];
    for(i = 0; i <= 9999; i++)
        sprintf(f[i], "%04d", i);
    while(t--) {
        scanf("%d", &n);
        char G[100][5], A[100], B[100];
        for(i = 0; i < n; i++) {
            scanf("%s %d/%d", G[i], &A[i], &B[i]);
        }
        int cnt = 0, ans;
        char s[5];
        for(i = 0; i <= 9999; i++) {
            s[0] = f[i][0];
            s[1] = f[i][1];
            s[2] = f[i][2];
            s[3] = f[i][3];
            for(j = 0; j < n; j++) {
                int num[10] = {}, a = 0, b = 0;
                for(k = 0; k < 4; k++) {
                    num[G[j][k]-'0']++;
                }
                for(k = 0; k < 4; k++) {
                    if(num[s[k]-'0'] > 0)
                        b++, num[s[k]-'0']--;
                }
                for(k = 0; k < 4; k++) {
                    if(s[k] == G[j][k])
                        a++, b--;
                }
                if(A[j] == a && B[j] == b)
                    continue;
                else
                    break;
            }
            if(j == n) {
                cnt++;
                ans = i;
                if(cnt == 2)
                    break;
            }
        }
        if(cnt == 1)
            printf("%04d\n", ans);
        else if(cnt == 0)
            puts("impossible");
        else
            puts("indeterminate");
    }
    return 0;
}
