#include <stdio.h>
#include <algorithm>
using namespace std;
long long dp[31][31];
long long A[31];
int used[31][31];
long long dfs(int l, int r) {
    if(l > r)   return 0;
    if(used[l][r])  return dp[l][r];
    int i;
    long long mx = 0;
    for(i = l; i <= r; i++) {
        if(l <= i-1 && i+1 <= r)
            mx = max(mx, dfs(l, i-1)*dfs(i+1, r)+A[i]);
        else if(l <= i-1)
            mx = max(mx, dfs(l, i-1)+A[i]);
        else if(i+1 <= r)
            mx = max(mx, dfs(i+1, r)+A[i]);
        else
            mx = max(mx, A[i]);
    }
    used[l][r] = 1;
    dp[l][r] = mx;
    return mx;
}
void print(int l, int r) {
    if(l > r)   return;
    int i;
    long long mx = dp[l][r], tmp;
    for(i = l; i <= r; i++) {
        if(l <= i-1 && i+1 <= r)
            tmp = dfs(l, i-1)*dfs(i+1, r)+A[i];
        else if(l <= i-1)
            tmp = dfs(l, i-1)+A[i];
        else if(i+1 <= r)
            tmp = dfs(i+1, r)+A[i];
        else
            tmp = A[i];
        if(mx == tmp) {
            printf("%d ", i+1);
            print(l, i-1);
            print(i+1, r);
            return;
        }
    }
}
int main() {
    int n, i;
    scanf("%d", &n);
    for(i = 0; i < n; i++)
        scanf("%lld", &A[i]);
    printf("%lld\n", dfs(0, n-1));
    print(0, n-1);
    return 0;
}
