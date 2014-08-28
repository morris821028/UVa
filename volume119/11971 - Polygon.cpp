#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <map>
#include <algorithm>
using namespace std;

long long gcd(long long x, long long y) {
    for (long long t; x%y; t = x, x = y, y = t%y);
    return y;
}
int main() {
    int n, k, cases = 0;
    scanf("%*d");
    while (scanf("%d %d", &n, &k) == 2) {
        long long a = k+1, b = 1LL<<k;
        long long g = gcd(a, b);
        a /= g, b /= g;
        a = b - a;
        printf("Case #%d: %lld/%lld\n", ++cases, a, b);
    }
    return 0;
}
/*
 
2D :
x1 + x2 + x3 = 1, (x1 < 1/2, x2 < 1/2, x1 + x2 > 1/2)/(x1 + x2 < 1, x1 > 0, x2 > 0) => area: 1/4

3D :
x1 + x2 + x3 + x4 = 1,
(x1 < 1/2, x2 < 1/2, x3 < 1/2, x1 + x2 + x3 > 1/2)
 
=> 1 - (k+1)/(2^(k))
*/