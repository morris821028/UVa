#include <stdio.h>
#include <string.h>
#define max(x, y) ((x) > (y) ? (x) : (y))

long long sum[501];
long long DP[501][501];
int best[501][501];
void solve(int n, int m, int A[]) {
    int i, j, k;
    memset(sum, 0, sizeof(sum));
    memset(DP[0], 127, sizeof(DP[0]));
    for(i = 1; i <= n; i++) {
        sum[i] = A[i] + sum[i-1];
    }
    DP[0][0] = 0;
    for(i = 1; i <= m; i++) {
        for(j = i; j <= n-(m-i); j++) {
            DP[i][j] = 0xffffffffffffffLL;
            for(k = i; k <= j; k++) {
                if(DP[i][j] > max(sum[j]-sum[k-1], DP[i-1][k-1])) {
                    best[i][j] = k-1;
                    DP[i][j] = max(sum[j]-sum[k-1], DP[i-1][k-1]);
                }
            }
        }
    }
    int path[501], p = 0;
    for(i = n, j = m-1; i >= 1; i--) {
        p += A[i];
        if(p > DP[m][n] || i <= j) {
            path[j--] = i+1;
            p = A[i];
        }
    }
    for(i = 1, j = 1; i <= n; i++) {
        if(j < k && i == path[j])
            printf("/ "), j++;
        printf("%d", A[i]);
        if(i != n)
            printf(" ");
    }
    puts("");
}
int main() {
    int t, n, m, A[501];
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        solve(n, m, A);
    }
    return 0;
}
