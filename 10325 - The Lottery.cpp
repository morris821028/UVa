#include <stdio.h>

int n, m, A[16], i, sum;
long long gcd(long long x, long long y) {
    long long t;
    while(x%y)
        t = x, x = y, y = t%y;
    return y;
}
void dfs(int idx, long long p, int cnt) {
    if(idx == m) {
        if(cnt&1)
            sum -= n/p;
        else
            sum += n/p;
        return;
    }
    if(p > n)       return;
    dfs(idx+1, p*A[idx]/gcd(p, A[idx]) , cnt+1);
    dfs(idx+1, p, cnt);
}
int main() {
    while(scanf("%d %d", &n, &m) == 2) {
        for(i = 0; i < m; i++)
            scanf("%d", &A[i]);
        sum = 0;
        dfs(0, 1, 0);
        printf("%d\n", sum);
    }
    return 0;
}
