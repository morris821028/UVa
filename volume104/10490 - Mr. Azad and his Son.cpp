#include <stdio.h>
#include <math.h>
int isprime(int n) {
    static int i;
    static long long j;
    j = sqrt(n);
    if(n < 2)  return 0;
    for(i = 2; i <= j; i++)
        if(n%i == 0)
            return 0;
    return 1;
}
int main() {
    long long n, a, b;
    while(scanf("%lld", &n) == 1 && n) {
        a = isprime(n);
        b = isprime((1LL<<n)-1);
        if(a && b)
            printf("Perfect: %lld!\n", (1LL<<(n-1))*((1LL<<n)-1));
        else if(a && !b)
            puts("Given number is prime. But, NO perfect number is available.");
        else
            puts("Given number is NOT prime! NO perfect number is available.");
    }
    return 0;
}
