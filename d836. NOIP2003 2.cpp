#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
int main() {
    int n, m, A[105];
    int i, j, k, l;
    scanf("%d %d", &n, &m);
    for(i = 0; i < n; i++)
        scanf("%d", &A[i]), A[n+i] = A[i];
    long long sum[105][105] = {};
    for(i = 0; i < 2*n; i++) {
        long long tmp = 0;
        for(j = i; j < 2*n; j++) {
            tmp += A[j];
            tmp %= 10;
            sum[i][j] = (tmp%10+10)%10;
        }
    }
    long long rmx = 0, rmn = 0xfffffff;
    for(i = 0; i < n; i++) {
        long long dp1[105][15];
        long long dp2[105][15];
        memset(dp1, 0, sizeof(dp1));//mx
        for(k = 0; k < i+n; k++)
            for(j = 0; j <= m; j++)
                dp2[k][j] = 1000000;
        for(k = i; k < i+n; k++) {
            for(j = k != i; j < m; j++) {
                for(l = k; l < i+n; l++) {
                    if(k != i)
                        dp1[l][j+1] = max(dp1[l][j+1], dp1[k-1][j]*sum[k][l]);
                    else
                        dp1[l][j+1] = max(dp1[l][j+1], sum[k][l]);
                    if(k != i)
                        dp2[l][j+1] = min(dp2[l][j+1], dp2[k-1][j]*sum[k][l]);
                    else
                        dp2[l][j+1] = min(dp2[l][j+1], sum[k][l]);
                }
            }
        }
        rmx = max(dp1[i+n-1][m], rmx);
        rmn = min(dp2[i+n-1][m], rmn);
    }
    printf("%lld\n%lld\n", rmn, rmx);
    return 0;
}
