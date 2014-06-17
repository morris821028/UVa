#include <stdio.h>

int main() {
    long long n;
    while(scanf("%lld", &n) == 1 && n) {
        printf("%lld\n", ((n*n*n*n*n*n)+3*n*n*n*n+12*n*n*n+8*n*n)/24);
    }
    return 0;
}
