#include <stdio.h>
#define LL long long
LL gcd(LL a, LL b) {
    LL t;
    while(a%b)
        t = a, a = b, b = t%b;
    return b;
}
LL lcm(LL a, LL b) {
    return a/gcd(a,b)*b;
}
int main() {
    int n, q, i, j, k, l;
    LL A[105], h;
    while(scanf("%d %d", &n, &q) == 2 && n) {
        for(i = 0; i < n; i++)
            scanf("%lld", &A[i]);
        while(q--) {
            scanf("%lld", &h);
            LL mx = 2147483647, mn = 2147483647;
            for(i = 0; i < n; i++) {
                for(j = i+1; j < n; j++) {
                    for(k = j+1; k < n; k++) {
                        for(l = k+1; l < n; l++) {
                            LL L = lcm(A[i], lcm(A[j], lcm(A[k], A[l])));
                            LL tmp = h%L, a;
                            a = L - tmp;
                            if(tmp == 0) {
                                mx = mn = 0;
                                i = j = k = l = n;
                            } else {
                                if(tmp < mn)  mn = tmp;
                                if(a < mx)  mx = a;
                            }
                        }
                    }
                }
            }
            printf("%lld %lld\n", h - mn, h + mx);
        }
    }
    return 0;
}
