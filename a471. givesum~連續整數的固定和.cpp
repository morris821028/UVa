#include <stdio.h>
#include <math.h>
int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        printf("%d\n", n);
        continue;
        n = n*2;
        int sol = 0;
        int sqq = sqrt(n), i;
        for(i = sqq; i >= 2; i--) {
            if(n%i == 0) {
                if((n/i+i-1)%2 == 0) {
                    printf("%d-%d\n", n/i-(n/i+i-1)/2, (n/i+i-1)/2);
                    sol = 1;
                }
            }
        }
        if(!sol)
            puts("No Solution...");
        puts("");
    }
    return n;
}
