#include <stdio.h>
#include <math.h>

int main() {
    int t, test = 0, n, x;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        printf("Case %d:", ++test);
        int i, sqr = sqrt(n);
        for(i = sqr-1; i >= 1; i--) {
            x = n-i*i;
            if(x%i == 0)
                printf(" %d", x);
        }
        puts("");
    }
    return 0;
}
