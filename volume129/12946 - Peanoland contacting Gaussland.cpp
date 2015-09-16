#include <stdio.h>
#include <complex>
using namespace std;

int main() {
    complex<long long> base(-1, 1);
    int p;
    while (scanf("%d", &p) == 1) {
        complex<long long> q(0, 0);
        for (complex<long long> t(1, 0); p; p >>= 1, t = t * base) {
            if (p&1)
                q = q + t;
        }
        printf("%lld %lld\n", q.real(), q.imag());
    }
    return 0;
}