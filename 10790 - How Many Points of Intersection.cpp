#include <stdio.h>

int main() {
    long long a, b;
    int cases = 0;
    while(scanf("%lld %lld", &a, &b) == 2) {
        if(a == 0 && b == 0)  break;
        printf("Case %d: %lld\n", ++cases,a*(a-1)/2*b*(b-1)/2);
    }
    return 0;
}
