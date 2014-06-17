#include <stdio.h>
#include <stdlib.h>
long long L(long long x, long long y) {
    int sum = 0, n;
    sum = y*(y+1)/2;
    n = x;
    sum += (2*(2+y)+n-1)*n/2;
    return sum;
}
int main() {
    int n, C = 0;
    scanf("%d", &n);
    while(n--) {
        long long x1, x2, y1, y2;
        scanf("%lld %lld %lld %lld", &x1, &y1, &x2, &y2);
        long long t1, t2, Ans;
        t1 = L(x1, y1);
        t2 = L(x2, y2);
        Ans = t1-t2;
        if(Ans < 0) Ans *= -1;
        printf("Case %d: %lld\n", ++C, Ans);
    }
    return 0;
}
