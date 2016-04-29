#include <stdio.h>
#include <algorithm>
using namespace std;

long long gcd(long long x, long long y) {
    long long t;
    while (x%y)
        t = x, x = y, y = t%y;
    return y;
}
long long lcm(long long x, long long y) {
    return x / gcd(x, y) * y;
}
int main() {
    int n;
    while (scanf("%d", &n) == 1 && n) {
        int A[128] = {}, used[128] = {};
        for (int i = 1; i <= n; i++)
            scanf("%d", &A[i]);
        long long ret = 1;
        for (int i = 1; i <= n; i++) {
            if (used[i])    continue;
            int u = i, cc = 0;
            while (!used[u])
                used[u] = 1, cc++, u = A[u];
            ret = lcm(ret, cc);
        }
        printf("%lld\n", ret);
    }
    return 0;
}
