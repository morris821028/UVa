#include <stdio.h>

int main() {
    long long s, d;
    while(scanf("%lld %lld", &s, &d) == 2) {
        long long i = s, sum = 0;
        while(1) {
            sum += i;
            if(sum >= d) {
                printf("%lld\n", i);
                break;
            }
            i++;
        }
    }
    return 0;
}
