#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, A[16];
    unsigned int dp[1<<15], a, b;
    while (scanf("%d %d", &n, &m) == 2) {
        for (int i = 1; i <= m; i++)
            scanf("%d", &A[i]);
        int ret = n;
        dp[0] = 1;
        for (int i = 1; i < (1<<m); i++) {
            long long val;
            a = dp[i-(i&(-i))], b = A[__builtin_ffs(i&(-i))];
            if (a > n) {dp[i] = n+1; continue;}
            val = b / __gcd(a, b) * (long long) a;
            if (val <= n) {
                dp[i] = val;
                if (__builtin_popcount(i)&1)
                    ret -= n / val;
                else
                    ret += n / val;
            } else {
                dp[i] = n+1;
            }
        }
        
        printf("%d\n", ret);
    }
    return 0;
}
