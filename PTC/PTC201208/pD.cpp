#include <stdio.h>
#include <string.h>
typedef struct {
    double v[501][501];
} Matrix;
Matrix muitaa(Matrix &a, Matrix &b, int n) {
    Matrix c;
    int i, j, k;
    memset(&c, 0, sizeof(c));
    for(i = 1; i <= n; i++) {
        for(j = 1; j <= n; j++) {
            c.v[1][j] += a.v[i][j] * b.v[1][i];
        }
    }
    return c;
}
Matrix F;
Matrix A;
int main() {
    int n, a, b;
    double v;
    while(scanf("%d", &n) == 1) {
        int m = n*n;
        for(int i = 0; i < m; i++) {
            scanf("%d:%d:%lf", &a, &b, &v);
            F.v[a][b] = v;
        }
        memset(&A, 0, sizeof(A));
        A.v[1][1] = 1;
        for(int i = 0; i < 100; i++) {
            A = muitaa(F, A, n);
        }
        double ans = 0;
        int at = 0;
        for(int i = 1; i <= n; i++)
            if(A.v[1][i] > ans)
                ans = A.v[1][i], at = i;
        printf("%d %d\n", at, (int)(ans*100));
    }
    return 0;
}
