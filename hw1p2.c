#include <stdio.h>
int solve(int l, int r, int n) {
    if(l > r)   return -1;
    int m = (l+r)/2;
    if(m*m <= n) {
        int tmp = solve(m+1, r, n);
        if(tmp < 0) return m;
        return tmp;
    }
    return solve(l, m-1, n);
}

int main() {
    int n;
    while(scanf("%d", &n) == 1)
        printf("%d\n", solve(0,n,n));
    return 0;
}
