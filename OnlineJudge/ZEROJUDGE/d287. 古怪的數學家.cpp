#include <stdio.h>
long long g(long long a, long long b) {
    long long t;
    while(a%b)
        t = a, a = b, b = t%b;
    return b;
}
int main() {
    long long a, b;
    while(scanf("%lld %lld", &a, &b) == 2)
        printf("%lld\n", a+b-g(a, b));
    return 0;
}
