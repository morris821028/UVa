#include <stdio.h>
#include <math.h>
int main() {
    long long n;
    while(scanf("%lld", &n) == 1) {
        long long i = sqrt(2*n)-1, sum = i*(i+1)/2;
        for(i++; ; i++) {
            if(sum+i >= n) {
                printf("%lld/%lld\n", i-n+sum+1, n-sum);
                break;
            }
            sum += i;
        }
    }
    return 0;
}
