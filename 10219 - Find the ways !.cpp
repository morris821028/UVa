#include <stdio.h>
#include <math.h>
int main() {
    unsigned long long a, b, i;
    while(scanf("%llu %llu", &a, &b) == 2) {
        long double sum = 0;
        for(i = a-b+1; i <= a; i++)
            sum += log10(i);
        for(i = b; i >= 1; i--)
            sum -= log10(i);
        printf("%d\n", (int)floor(sum)+1);
    }
    return 0;
}
