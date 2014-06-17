#include <stdio.h>
#include <math.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n >= 0) {
        printf("%d coconuts, ", n);
        int sol = 0, i, j;
        int sq = (int)sqrt(n)+1;
        for(i = sq; i >= 2; i--) {
            int ans = n;
            for(j = 1; j <= i; j++) {
                if(ans%i != 1)
                    break;
                ans = ans - ans/i - 1;
            }
            if(j == i+1 && ans%i == 0) {
                sol = 1;
                printf("%d people and 1 monkey\n", i);
                break;
            }
        }
        if(!sol)
            puts("no solution");
    }
    return 0;
}
