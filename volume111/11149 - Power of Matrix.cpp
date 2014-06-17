#include<stdio.h>
typedef struct {
    int t[40][40];
}Matrix;
Matrix A, In, init, Ans;
Matrix mult(Matrix x, Matrix  y, int n) {
    Matrix t = init;
    int i, j, k;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k = 0; k < n; k++) {
                t.t[i][k] += x.t[i][j]*y.t[j][k];
            }
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            t.t[i][j] %= 10;
    return t;
}
Matrix add(Matrix x, Matrix  y, int n) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            x.t[i][j] = (x.t[i][j] + y.t[i][j]) % 10;
    return x;
}
Matrix Calu_Ak(int k, int n) {
    Matrix x = In, y = A;
    while(k) {
        if(k&1) x = mult(x, y, n);
        y = mult(y, y, n);
        k /= 2;
    }
    return x;
}

Matrix Calu_total(int n, int k) {
    if(k == 0) return init;
    
    if(k&1) {
        return add(mult(Calu_total(n, k/2), add(In, Calu_Ak(k/2, n), n), n), Calu_Ak(k, n), n);
    }
    else {
        return mult(Calu_total(n, k/2), add(In, Calu_Ak(k/2, n), n), n);
    }
}
main() {
    int n, a, b, k, x, y, s;
    while(scanf("%d %d", &n, &k) == 2 && n) {
        for(a = 0; a < n; a++)
            for(b = 0; b < n; b++)
                A.t[a][b] = 0, In.t[a][b] = 0,
                init.t[a][b] = 0;
        for(a = 0; a < n; a++) In.t[a][a] = 1;
        for(a = 0; a < n; a++)
            for(b = 0; b < n; b++)
                scanf("%d", &A.t[a][b]), A.t[a][b] %= 10;
        Ans = Calu_total(n, k);
        for(a = 0; a < n; a++, puts(""))
            for(b = 0; b < n; b++) {
                printf("%d", Ans.t[a][b]);
            	if(b != n-1)
            		printf(" ");
			}
		puts("");
    }
    return 0;
}
