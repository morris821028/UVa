#include <stdio.h>
#include <stdlib.h>
#define min(x,y) ((x)<(y)?(x):(y))
typedef struct {
    int t, c, in;
} St;
int cmp(const void *i, const void *j) {
    return ((St *)i)->t - ((St *)j)->t;
}
int cmp_out(const void *i, const void *j) {
    return ((St *)i)->in - ((St *)j)->in;
}
int st[10005][6][6][5];
int main() {
    int t, n, i, j, k;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        St D[10005];
        for(i = 0; i < n; i++)
            scanf("%d %d", &D[i].t, &D[i].c), D[i].c /= 10, D[i].in = i;
        qsort(D, n, sizeof(St), cmp);
        int dp[10005][6][6] = {}, ch = 0;
        for(i = 1; i <= 5; i++)
            for(j = 1; j <= 5; j++)
                dp[0][i][j] = 0xfffffff;
        dp[0][1][1] = 0;
        for(i = 0; i < n; i++) {
            ch++;
            for(j = 1; j <= 5; j++)
                for(k = 1; k <= 5; k++)
                    dp[ch][j][k] = 0xfffffff;
            if(i+1 < n && D[i+1].t == D[i].t) {
                st[ch][D[i].c][D[i+1].c][0] = 2;/*[0]cnt*/
                st[ch][D[i+1].c][D[i].c][0] = 2;
                for(j = 1; j <= 5; j++) {
                    for(k = 1; k <= 5; k++) {
                        if(dp[ch][D[i].c][D[i+1].c] > dp[ch-1][j][k]+abs(j-D[i].c)+abs(k-D[i+1].c)) {
                            dp[ch][D[i].c][D[i+1].c] = dp[ch-1][j][k]+abs(j-D[i].c)+abs(k-D[i+1].c);
                            st[ch][D[i].c][D[i+1].c][1] = j;/*state*/
                            st[ch][D[i].c][D[i+1].c][2] = k;
                            st[ch][D[i].c][D[i+1].c][3] = 1;/*choose*/
                            st[ch][D[i].c][D[i+1].c][4] = 2;
                        }
                        if(dp[ch][D[i+1].c][D[i].c] > dp[ch-1][j][k]+abs(k-D[i].c)+abs(j-D[i+1].c)) {
                            dp[ch][D[i+1].c][D[i].c] = dp[ch-1][j][k]+abs(k-D[i].c)+abs(j-D[i+1].c);
                            st[ch][D[i+1].c][D[i].c][1] = j;
                            st[ch][D[i+1].c][D[i].c][2] = k;
                            st[ch][D[i+1].c][D[i].c][3] = 2;
                            st[ch][D[i+1].c][D[i].c][4] = 1;
                        }
                    }
                }
                i++;
            } else {
                for(j = 1; j <= 5; j++) {
                    for(k = 1; k <= 5; k++) {
                        if(dp[ch][D[i].c][k] > dp[ch-1][j][k]+abs(j-D[i].c)) {
                            dp[ch][D[i].c][k] = dp[ch-1][j][k]+abs(j-D[i].c);
                            st[ch][D[i].c][k][0] = 1;
                            st[ch][D[i].c][k][1] = j;
                            st[ch][D[i].c][k][2] = k;
                            st[ch][D[i].c][k][3] = 1;
                        }
                        if(dp[ch][j][D[i].c] > dp[ch-1][j][k]+abs(k-D[i].c)) {
                            dp[ch][j][D[i].c] = dp[ch-1][j][k]+abs(k-D[i].c);
                            st[ch][j][D[i].c][0] = 1;
                            st[ch][j][D[i].c][1] = j;
                            st[ch][j][D[i].c][2] = k;
                            st[ch][j][D[i].c][3] = 2;
                        }
                    }
                }
            }
        }
        int ans = 0xfffffff;
        for(i = 1; i <= 5; i++)
            for(j = 1; j <= 5; j++)
                ans = min(ans, dp[ch][i][j]+i+j-2);
        int ti, tj;
        for(i = 1; i <= 5; i++)
            for(j = 1; j <= 5; j++)
                if(ans == dp[ch][i][j]+i+j-2)
                    ti = i, tj = j;
        int pel = n-1;
        while(ch > 0) {
            if(st[ch][ti][tj][0] == 1) {
                D[pel].t = st[ch][ti][tj][3];
                int tti = st[ch][ti][tj][1];
                int ttj = st[ch][ti][tj][2];
                ti = tti, tj = ttj;
                pel--;
            } else {
                D[pel].t = st[ch][ti][tj][4];
                D[pel-1].t = st[ch][ti][tj][3];
                int tti = st[ch][ti][tj][1];
                int ttj = st[ch][ti][tj][2];
                ti = tti, tj = ttj;
                pel -= 2;
            }
            ch--;
        }
        qsort(D, n, sizeof(St), cmp_out);
        ans = ans*10 + n*15;
        printf("%d\n", ans);
        for(i = 0; i < n; i++)
            printf("%d\n", D[i].t);
    }
    return 0;
}
