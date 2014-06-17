#include <stdio.h>

int main() {
    int n, k, i, j;
    while(scanf("%d %d", &n, &k) == 2) {
        if(n < 0)   break;
        long long c[10005];
        for(i = n; i >= 0; i--)
            scanf("%lld", &c[i]);
        for(i = 0; i <= n-k; i++) {
            c[i+k] -= c[i];
            c[i] = 0;
        }
        i = 0;
        while(c[i] == 0 && i <= n) i++;
        if(n < i)   printf("0");
        for(j = n; j >= i; j--) {
            if(j != n)  printf(" ");
            printf("%lld", c[j]);
        }
        puts("");
    }
    return 0;
}
