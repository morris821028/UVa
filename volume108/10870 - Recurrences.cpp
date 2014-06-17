#include <stdio.h>
#include <string.h>
struct M {
    int v[16][16];
} o, I;
void mult(M &a, M &b, int m, int d) {
    static int i, j, k;
    static M t;
    t = o;
    for(i = 0; i < d; i++) {
        for(j = 0; j < d; j++) {
            for(k = 0; k < d; k++) {
                t.v[i][j] += a.v[i][k]*b.v[k][j];
                t.v[i][j] %= m;
            }
        }
    }
    a = t;
}
M solve(int n, int m, M base, int d) {
    M x = I, y = base;
    while(n) {
        if(n&1)
            mult(x, y, m, d);
        mult(y, y, m, d);
        n /= 2;
    }
    return x;
}
int main() {
    int d, n, m, a[16], f[16];
    int i;
    memset(&o, 0, sizeof(M));
    I = o;
    for(i = 0; i < 16; i++)
        I.v[i][i] = 1;
    while(scanf("%d %d %d", &d, &n, &m) == 3) {
        if(d == 0)
            break;
        for(i = 0; i < d; i++)
            scanf("%d", &a[i]), a[i] %= m;
        for(i = 0; i < d; i++)
            scanf("%d", &f[i]), f[i] %= m;
        M base = o, res;
        for(i = 0; i < d; i++)
            base.v[i][0] = a[i];
        for(i = 1; i < d; i++)
            base.v[i-1][i] = 1;

        res = solve(n-1, m, base, d);
        int ans = 0;
        for(i = 0; i < d; i++) {
            ans += res.v[i][d-1]*f[d-i-1];
            ans %= m;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
