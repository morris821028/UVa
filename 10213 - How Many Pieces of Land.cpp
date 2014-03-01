#include <stdio.h>

int main() {
    long long n;
    scanf("%*d");
    while(scanf("%lld", &n) == 1)
        printf("%lld\n", n*(n-1)*(n-2)*(n-3)/24 + n*(n-1)/2 + 1);
    return 0;
}
