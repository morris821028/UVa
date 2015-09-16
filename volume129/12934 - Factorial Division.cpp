#include <stdio.h>
#include <algorithm>
using namespace std;

void solve(long long x) {
    for (long long n = 2; n * (n-1) <= x; n++) {
        long long pp = n;
        for (long long m = n-1; m >= 1 && pp <= x; m--) {
            if (pp == x) {
                printf("%lld %lld\n", n, m);
                return ;
            }
            pp *= m;
        }
    }
    printf("%lld %lld\n", x, x-1);
}
int main() {
    int cases = 0;
    long long x;
    while (scanf("%lld", &x) == 1) {
        printf("Case %d: ", ++cases);
        if (x < 2)
            puts("Impossible");
        else
            solve(x);
    }
    return 0;
}