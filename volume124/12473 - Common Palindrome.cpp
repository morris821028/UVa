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
5
gabgcccbadacg
gabxxxbacccgbadab
Case 1: 7
3
cfcfaafc
efagfc
afbcdfca
bcadfcgyfka
palin
drome
Case 1: 3
Case 2: 5
Case 3: 0
5
a
b
*/
