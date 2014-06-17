#include <stdio.h>

int main() {
    int n, k, i;
    while(scanf("%d", &n) == 1) {
        if(n <= 3) {
            puts("Impossible");
            continue;
        }
        if(n%6 != 2 && n%6 != 3) {
            printf("2");
            for(i = 4; i <= n; i += 2)
                printf(" %d", i);
            for(i = 1; i <= n; i += 2)
                printf(" %d", i);
        } else {
            if(n&1) k = (n-1)/2;
            else    k = n/2;
            if(k%2 == 0 && n%2 == 0) {
                printf("%d", k);
                for(i = k+2; i <= n; i += 2)
                    printf(" %d", i);
                for(i = 2; i <= k-2; i += 2)
                    printf(" %d", i);
                for(i = k+3; i <= n-1; i += 2)
                    printf(" %d", i);
                for(i = 1; i <= k+1; i += 2)
                    printf(" %d", i);
            }
            if(k%2 == 0 && n%2 == 1) {
                printf("%d", k);
                for(i = k+2; i <= n-1; i += 2)
                    printf(" %d", i);
                for(i = 2; i <= k-2; i += 2)
                    printf(" %d", i);
                for(i = k+3; i <= n-2; i += 2)
                    printf(" %d", i);
                for(i = 1; i <= k+1; i += 2)
                    printf(" %d", i);
                printf(" %d", n);
            }
            if(k%2 == 1 && n%2 == 0) {
                printf("%d", k);
                for(i = k+2; i <= n-1; i += 2)
                    printf(" %d", i);
                for(i = 1; i <= k-2; i += 2)
                    printf(" %d", i);
                for(i = k+3; i <= n; i += 2)
                    printf(" %d", i);
                for(i = 2; i <= k+1; i += 2)
                    printf(" %d", i);
            }
            if(k%2 == 1 && n%2 == 1) {
                printf("%d", k);
                for(i = k+2; i <= n-2; i += 2)
                    printf(" %d", i);
                for(i = 1; i <= k-2; i += 2)
                    printf(" %d", i);
                for(i = k+3; i <= n-1; i += 2)
                    printf(" %d", i);
                for(i = 2; i <= k+1; i += 2)
                    printf(" %d", i);
                printf(" %d", n);
            }
        }
        puts("");
    }
    return 0;
}
