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
    turtle A[5700];
    int n = 0, i, j;
    while(scanf("%d %d", &A[n].w, &A[n].s) == 2)
        n++;
    sort(A, A+n, cmp);
    int dp[5700];
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
    return 0;
}
