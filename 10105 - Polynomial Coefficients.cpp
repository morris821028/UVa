#include <stdio.h>

int main() {
    int n, k;
    int f[15] = {1};
    for(n = 1; n < 15; n++)
        f[n] = f[n-1]*n;
    while(scanf("%d %d", &n, &k) == 2) {
        int ans = f[n];
        while(k--) {
            scanf("%d", &n);
            ans /= f[n];
        }
        printf("%d\n", ans);
    }
    return 0;
}
