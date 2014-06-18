#include <stdio.h>
long long digit[50] = {1};

long long cntOnes(long long n) {
    if(n < 1)  return 0;
    if(n == 1)  return 1;
    long long sum = 0;
    int i, high_bit;
    for(i = 0; i < 40; i++) {
        if((n>>i)&1)
            high_bit = i;
    }
    if(high_bit)
        sum += digit[high_bit-1];
    return sum + (n-(1LL<<high_bit)+1) + cntOnes(n-(1LL<<high_bit));
}
int main() {
    int i, cases = 0;
    long long a, b;
    for(i = 1; i < 50; i++)
        digit[i] = (digit[i-1]<<1) + (1<<i);
    while(scanf("%lld %lld", &a, &b) == 2) {
        if(a == 0 && b == 0)
            break;
        printf("Case %d: %lld\n", ++cases, cntOnes(b)-cntOnes(a-1));
    }
    return 0;
}
