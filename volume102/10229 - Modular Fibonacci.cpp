#include <stdio.h>
struct M {
    long long v[2][2];
} I = {1,0,0,1}, o = {0,0,0,0}, A = {1,1,1,0};
void mult(M &a, M &b, int m) {
    static int i, j, k;
    M t = o;
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 2; j++) {
            for(k = 0; k < 2; k++) {
                t.v[i][j] += a.v[i][k]*b.v[k][j];
                t.v[i][j] &= (1<<m)-1;
            }
        }
    }
    a = t;
}
void calc(int n, int m) {
    M x = I, y = A;
    while(n) {
        if(n&1) mult(x, y, m);
        mult(y, y, m);
        n /= 2;
    }
    printf("%lld\n", x.v[0][2]);
}
int main() {
    int n, m;
    while(~scanf("%d %d", &n, &m))
        calc(n, m);
    return 0;
}
