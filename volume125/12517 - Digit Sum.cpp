#include <stdio.h>
#define LL long long
LL calc(LL n, LL dep, LL lef) {
    if(n == 0)  return 0;
    LL m = n%10;
    return n/10*45*dep + m*lef + m*(m-1)/2*dep + calc(n/10, dep*10, lef+m*dep);
}
int main() {
    int m, n;
    while(scanf("%d %d", &m, &n) == 2 && n)
        printf("%lld\n", calc(n,1,1)-calc(m-1,1,1));
    return 0;
}
