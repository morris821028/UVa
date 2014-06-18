#include <stdio.h>
#include <math.h>

int main() {
    int t;
    long long n;
    scanf("%d", &t);
    while(t--) {
        scanf("%lld", &n);
        printf("%lld\n", (long long)floor(sqrt( 2.0 * n + 0.25 ) + 0.5) - 1);
    }
    return 0;
}
