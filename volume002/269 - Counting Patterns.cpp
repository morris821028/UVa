#include <stdio.h>
void dfs(int idx, int n, int k, int a[], int b[], int sum) {
    if(idx == n) {
        if(sum < 0)
            b[-sum]++;
        else
            a[sum]++;
        return;
    }
    int i;
    for(i = -k; i <= k; i++) {
        dfs(idx+1, n, k, a, b, sum+i);
    }
}
int main() {
    int n, k, i;
    while(scanf("%d %d", &n, &k) == 2) {
        int a1[1000] = {}, b1[1000] = {};
        int a2[1000] = {}, b2[1000] = {};
        dfs(0, n/2, k, a1, b1, 0);
        dfs(0, n-n/2, k, a2, b2, 0);
        long long res = 0;
        for(i = 1; i < 1000; i++)
            res += a1[i]*b2[i] + a2[i]*b1[i];
        res += a1[0]*a2[0];
        printf("%lld\n", res);
    }
    return 0;
}
