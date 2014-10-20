#include <stdio.h>
#include <stack>
#include <algorithm>
#include <string.h>
#include <functional>
#define MAXN 1024
using namespace std;

char A[32767], B[32767];
const char hand[] = "RPS";
double dp[131072][3], edp[131072][3];
int resultRPS(char a, char b) {
    if (a == b) return 0;
    if (a == 'R' && b == 'P')
        return -1;
    if (a == 'P' && b == 'S')
        return -1;
    if (a == 'S' && b == 'R')
        return -1;
    return 1;
}
int rps2num(char a) {
    if (a == 'R')   return 0;
    if (a == 'P')   return 1;
    if (a == 'S')   return 2;
    return 0;
}
// rock-paper-scissors

int main() {
    int testcase;
    int n;
    scanf("%d", &testcase);
    while(testcase--) {
        scanf("%s %s", A, B);
        n = (int) strlen(A);
        double R, P, S;
        scanf("%lf %lf %lf", &R, &P, &S);
        int oscore = 0;
        for (int i = 0; i < n; i++)
            oscore += resultRPS(A[i], B[i]);
        memset(dp, 0, sizeof(dp));
        memset(edp, 0, sizeof(edp));
        R /= 100, P /= 100, S /= 100;
        dp[0][0] = R;
        dp[0][1] = P;
        dp[0][2] = S;
        for (int i = 0; i < n; i++) {
            for (int p = 0; p < 3; p++) { // now
                if (resultRPS(hand[p], B[i]) == 0) {
                    dp[i+1][0] += dp[i][p] * R;
                    dp[i+1][1] += dp[i][p] * P;
                    dp[i+1][2] += dp[i][p] * S;
                    edp[i+1][0] += edp[i][p] * R;
                    edp[i+1][1] += edp[i][p] * P;
                    edp[i+1][2] += edp[i][p] * S;
                } else if (resultRPS(hand[p], B[i]) == 1) {
                    dp[i+1][(p+1)%3] += dp[i][p];
                    edp[i+1][(p+1)%3] += edp[i][p] + 1 * dp[i][p];
                } else {
                    int q = rps2num(B[i]);
                    dp[i+1][(q+1)%3] += dp[i][p];
                    edp[i+1][(q+1)%3] += edp[i][p] - 1 * dp[i][p];
                }
            }
        }
        double e = edp[n][0] + edp[n][1] + edp[n][2];
        printf("%d %.4lf %c\n", oscore, e, e > oscore ? 'Y' : 'N');
    }
    return 0;
}
/*
 4
 SPR
 PPR
 5 80 15
 RRR
 PPR
 5 80 15
 S
 S
 33 34 33
 S
 S
 34 33 33
*/
