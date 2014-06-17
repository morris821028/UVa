#include <stdio.h>
#include <string.h>
typedef struct {
    int v[30][30];
} matrix;
matrix In;
matrix multiply(matrix a, matrix b, int n) {
    static matrix c;
    static int i, j, k;
    memset(&c, 0, sizeof(matrix));
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k = 0; k < n; k++)
                c.v[i][j] += a.v[i][k]*b.v[k][j];
    return c;
}
void solve(int n, int m, matrix A) {
    matrix x = In, y = A;
    while(m) {
        if(m&1)
            x = multiply(x, y, n);
        m /= 2;
        y = multiply(y, y, n);
    }
    printf("%d\n", x.v[0][0]);
}
int main() {
    int n, m, i;
    memset(&In, 0, sizeof(matrix));
    for(i = 0; i < 30; i++)
        In.v[i][i] = 1;
    matrix A;
    while(scanf("%d %d", &n, &m) == 2) {
        memset(&A, 0, sizeof(matrix));
        for(i = 0; i < n; i++) {
            A.v[i][(i+1)%n] = 1;
            A.v[i][(i-1+n)%n] = 1;
        }
        solve(n, m, A);
    }
    return 0;
}
