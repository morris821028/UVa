#include <stdio.h>
#define LL long long
struct mx {
    LL v[2][2];
};
mx o = {1,0,0,1}, A = {3,1,1,0};
mx mult(mx x, mx y, LL mod) {
    mx z = {0,0,0,0};
    int i, j, k;
    for(i = 0; i < 2; i++)
        for(j = 0; j < 2; j++)
            for(k = 0; k < 2; k++) {
                z.v[j][k] += x.v[j][i]*y.v[i][k];
                z.v[j][k] %= mod;
            }
    return z;
}
LL g(LL y, LL mod) {
    mx x = o, a = A;
    while(y) {
        if(y&1)
            x = mult(x, a, mod);
        y /= 2;
        a = mult(a, a, mod);
    }
    return x.v[1][0];
}
int main() {
    LL n;
    while(scanf("%I64d", &n) == 1) {
        printf("%I64d\n", g(g(g(n, 183120LL), 222222224LL), 1000000007LL));
    }
    return 0;
}
/*
int main() {
    LL g0 = 0, g1 = 1, g;
    const LL mod = 1000000007LL;
    const LL mod2 = 222222224LL;
    const LL mod3 = 183120LL;
    for(LL i = 1; ; i++) {
        g = g1*3 + g0;
        //g %= mod;
        g %= mod2;
        g0 = g1, g1 = g;
        if(g0 == 0 && g1 == 1) {
            printf("%lld\n", i);
            break;
        }
    }
    return 0;
}*/
