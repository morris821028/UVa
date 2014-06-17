#include <stdio.h>
struct matrix {
    long long v[2][2];
} A = {0,1,2,2}, I = {1,0,0,1}, O = {0,0,0,0};
matrix multiply(matrix a, matrix b, int mod) {
    matrix c = O;
    int i, j, k;
    for(i = 0; i < 2; i++)
        for(j = 0; j < 2; j++)
            for(k = 0; k < 2; k++)
                c.v[i][j] += a.v[i][k]*b.v[k][j];
    for(i = 0; i < 2; i++)
        for(j = 0; j < 2; j++)
            c.v[i][j] %= mod;
    return c;
}
matrix calc(int T, int mod) {
    matrix x, y;
    x = I, y = A;
    while(T) {
        if(T&1)
            x = multiply(x, y, mod);
        T /= 2;
        y = multiply(y, y, mod);
    }
    return x;
}
int main() {
    scanf("%*d");
    int N, M, D, T;
    while(scanf("%d %d %d %d", &N, &M, &D, &T) == 4) {
        matrix P = calc(T, N);
        printf("%lld %lld\n", (P.v[0][0]*M+P.v[0][1]*D)%N, (P.v[1][0]*M+P.v[1][1]*D)%N);
    }
    return 0;
}
