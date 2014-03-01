#include <stdio.h>

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n > 0) {
        printf("%d = ", n);
        n = n*2;
        long long i, x, y, a, b;
        long long rx = n/2, ry = n/2;
        for(i = 2; i*i <= n; i++) {
            if(n%i == 0) {
                a = n/i, b = i;
                if((a-b+1)&1)
                    continue;
                if((a+b-1)&1)
                    continue;
                x = (a-b+1)/2;
                y = (a+b-1)/2;
                if(y-x+1 > ry-rx+1)
                    rx = x, ry = y;
            }
        }
        printf("%lld + ... + %lld\n", rx, ry);
    }
    return 0;
}
/*
n = x + ... + y
(x+y)*(y-x+1) = 2*n = a*b
 x+y = a
-x+y = b-1
x = (a-b+1)/2;
y = (a+b-1)/2;
*/
