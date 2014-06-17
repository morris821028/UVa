#include <stdio.h>
#include <math.h>
int main() {
    int n, i;
    while(scanf("%d", &n) == 1 && n) {
        n = (n-1960)/10+2;
        double m = 1<<n;
        for(i = 1; m > 0; i++)
            m -= log10(i)/log10(2);
        printf("%d\n", i-2);
    }
    return 0;
}
