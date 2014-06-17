#include <stdio.h>
#include <math.h>

int main() {
    long long n;
    int cases = 0;
    while(scanf("%lld", &n), n) {
        long long m = sqrt(n*2);
        while(m*(m-1)/2-m < n)
            m++;
        printf("Case %d: %lld\n", ++cases, m);
    }
    return 0;
}
