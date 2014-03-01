#include <stdio.h>
#include <algorithm>
using namespace std;
int main() {
    int t, A[50], B[50];
    int i, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        for(i = 0; i < n; i++) {
            scanf("%d %d", &A[i], &B[i]);
        }
        int i = 0, j = 0, flag = 0;
        int dp[50][50] = {};
        while(i < n && j < n) {
            if(i > j) {
                dp[i][j+4] = max(dp[i][j+4], dp[i][j]+B[j]*B[j+3]+B[j+1]+B[j+2]);
                dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]+A[i]*B[j]);
            } else if(j > i) {

            } else {
            }
            if(flag)    i += 2;
            else        j += 2;
            flag = 1-flag;
        }
    }
    return 0;
}
