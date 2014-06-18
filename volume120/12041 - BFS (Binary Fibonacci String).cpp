#include <stdio.h>
#include <algorithm>
using namespace std;
long long f[50];
void fib_bit(int n, long long l, long long r) {
    if(l > r)   return;
    if(n == 0)  putchar('0');
    else if(n == 1)  putchar('1');
    else {
        if(l < f[n-2]) {
            fib_bit(n-2, l, min(r, f[n-2]-1));
            fib_bit(n-1, 0, r-f[n-2]);
        } else {
            fib_bit(n-1, l-f[n-2], r-f[n-2]);
        }
    }
}
int main() {
    int t, i;
    long long n, a, b;
    f[0] = 1, f[1] = 1;
    for(a = 2; a <= 50; a++)
        f[a] = f[a-1]+f[a-2];
    scanf("%d", &t);
    while(t--) {
        scanf("%lld %lld %lld", &n, &a, &b);
        if(n >= 48)
            n = 48 - (n%2);
        fib_bit(n, a, b);
        puts("");
    }
    return 0;
}
