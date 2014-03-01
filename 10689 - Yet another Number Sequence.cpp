#include <stdio.h>
#include <math.h>
struct M {
    int v[2][2];
} I = {1,0,0,1}, o = {0,0,0,0}, A = {1,1,1,0};
void mult(M &a, M &b, int m) {
    static int i, j, k;
    M t = o;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            for(k = 0; k < 2; k++) {
                t.v[i][j] += a.v[i][k]*b.v[k][j];
                t.v[i][j] %= m;
            }
        }
    }
    a = t;
}
M calc(int n, int m) {
    M x = I, y = A;
    while(n) {
        if(n&1) mult(x, y, m);
        mult(y, y, m);
        n /= 2;
    }
    return x;
}
int main() {
    int n, m, a, b, t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d %d %d", &a, &b, &n, &m);
        m = (int)pow(10, m);
        M res = calc(n, m);
        int ans = res.v[1][0]*b+res.v[1][1]*a;
        printf("%d\n", ans%m);
    }
    return 0;
}
