#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char dp[65][65][65][65];

int main() {
    int t, cases = 0;
    int i, j, k, p, q, r;
    int a1, b1, c1, d1;
    char A[105], B[105];
    scanf("%d", &t);
    while(t--) {
        scanf("%s %s", &A, &B);
        int la = strlen(A), lb = strlen(B);
        memset(dp, 0, sizeof(dp));
        int usedA[128] = {}, usedB[128] = {};
        for(i = 0; i < la; i++)
            usedA[A[i]-'a'] = 1;
        for(i = 0; i < lb; i++)
            usedB[B[i]-'a'] = 1;
        for(i = 0, j = 0; i < la; i++)
            if(usedB[A[i]-'a'])
                A[j++] = A[i];
        A[j] = '\0';
        for(i = 0, j = 0; i < lb; i++)
            if(usedA[B[i]-'a'])
                B[j++] = B[i];
        B[j] = '\0';
        la = strlen(A);
        lb = strlen(B);
        if(la == 0 || lb == 0) {
            printf("Case %d: 0\n", ++cases);
            continue;
        }
        for(i = 0; i < la; i++) {
            for(j = 0; j < lb; j++) {
                if(A[i] == B[j])
                    dp[i][i][j][j] = 1;
            }
        }
        for(i = 0; i < la; i++) {
            for(j = 0; i+j < la; j++) {
                for(p = 0; p < lb; p++) {
                    for(q = 0; p+q < lb; q++) {
                        if(A[j] == A[i+j] && B[q] == B[p+q] && p && i && A[j] == B[q]) {
                            dp[j][i+j][q][p+q] = dp[j+1][i+j-1][q+1][p+q-1]+2;
                            //printf("(%d %d %d %d)%d\n", j, i+j, q, p+q, dp[j+1][i+j-1][q+1][p+q-1]);
                        }
                        if(j+1 <= i+j)
                        dp[j][i+j][q][p+q] = max(dp[j][i+j][q][p+q], dp[j+1][i+j][q][p+q]);
                        if(j <= i+j-1)
                        dp[j][i+j][q][p+q] = max(dp[j][i+j][q][p+q], dp[j][i+j-1][q][p+q]);
                        if(q+1 <= p+q)
                        dp[j][i+j][q][p+q] = max(dp[j][i+j][q][p+q], dp[j][i+j][q+1][p+q]);
                        if(q <= p+q-1)
                        dp[j][i+j][q][p+q] = max(dp[j][i+j][q][p+q], dp[j][i+j][q][p+q-1]);
                        //printf("(%d %d %d %d) dp %d\n", j, i+j, q, p+q, (int)dp[j][i+j][q][p+q]);
                    }
                }
            }
        }
        printf("Case %d: %d\n", ++cases, dp[0][la-1][0][lb-1]);
    }
    return 0;
}
/*
3
cfcfaafc
efagfc
afbcdfca
bcadfcgyfka
palin
drome
*/
