#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
unsigned long long seed;
long double gen()
{
    static const long double Z = ( long double )1.0 / (1LL<<32);
    seed >>= 16;
    seed &= ( 1ULL << 32 ) - 1;
    seed *= seed;
    return seed * Z;
}
int main() {
    int testcase, cases = 0, n;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %llu", &n, &seed);
        long double sum = 0, sum2 = 0, ret = 0, x, m;
        for (int i = 0; i < n; i++) {
            x = gen();
            sum += x;
            sum2 += x * x;
        }
        m = sum / n;
        ret = (sum2 - 2 * m * sum)/n + m * m;
        ret = sqrt(ret);
        printf("Case #%d: %.5lf\n", ++cases, (double) ret);
    }
    return 0;
}
/*
 5
 2 16777216
 2 4294967296
 10000000 0
 2 2147483648
 10000 382759482784958
*/