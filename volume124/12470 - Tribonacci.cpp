#include <stdio.h>
#define mod 1000000009
struct M {
    long long v[3][3];
} I = {1,0,0,0,1,0,0,0,1},
    o = {0,0,0,0,0,0,0,0,0},
    A = {1,1,0,1,0,1,1,0,0};
void multiply(M &x, M &y) {
    static int i, j, k;
    static M t;
    t = o;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            for(k = 0; k < 3; k++) {
                t.v[i][j] += x.v[i][k]*y.v[k][j];
                t.v[i][j] %= mod;
            }
        }
    }
    x = t;
}
M solve(long long n) {
    M x = I, y = A;
    while(n > 0) {
        if(n&1)
            multiply(x, y);
        n /= 2;
        multiply(y, y);
    }
    return x;
}
int main() {
    long long n;
    while(scanf("%lld", &n) == 1 && n) {
        if(n == 1)
            puts("0");
        else if(n == 2)
            puts("1");
        else if(n == 3)
            puts("2");
        else {
            M res = solve(n-3);
            printf("%lld\n", (res.v[1][0]+res.v[0][0]*2)%mod);
        }
    }
    return 0;
}
