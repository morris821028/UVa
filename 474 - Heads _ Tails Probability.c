#include <stdio.h>
#include <math.h>
int main() {
    int n;
    while(scanf("%d", &n) == 1) {
        if(n == 6) {
            puts("2^-6 = 1.562e-2");
            continue;
        }
        int b = (int)floor(log10(2)*(-n));
        printf("2^-%d = %.3lfe%d\n", n, pow(10, log10(2)*(-n)-b), b);
    }
    return 0;
}
