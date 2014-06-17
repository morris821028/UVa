#include <stdio.h>
#include <algorithm>
using namespace std;
struct turtle {
    int w, s;
};
bool cmp(turtle a, turtle b) {
    return a.s < b.s;
}
int main() {
    turtle A[1005];
    int n, i, j;
    while(scanf("%d", &n) == 1 && n) {
        for(i = n-1; i >= 0; i--)
            scanf("%d %d", &A[i].w, &A[i].s), A[i].s += A[i].w;
        int dp[1005];
        for(i = 0; i <= n; i++)
            dp[i] = 0xfffffff;
        dp[0] = 0;
        for(i = 0; i < n; i++) {
            for(j = n; j >= 1; j--) {
                if(dp[j-1]+A[i].w <= A[i].s) {
                    dp[j] = min(dp[j], dp[j-1]+A[i].w);
                }
            }
        }
        for(i = n; i >= 0; i--) {
            if(dp[i] != 0xfffffff)
                break;
        }
        printf("%d\n", i);
    }
    return 0;
}
