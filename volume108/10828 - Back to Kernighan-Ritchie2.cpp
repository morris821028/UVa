#include <stdio.h>
#include <vector>
#define eps 1e-6
using namespace std;
struct Matrix {
    float t[100][100];
};
Matrix A, In, init, res;
Matrix mult(Matrix x, Matrix y, int n) {
    Matrix t = init;
    static int i, j, k;
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(k = 0; k < n; k++) {
                t.t[i][k] += x.t[i][j]*y.t[j][k];
            }
        }
    }
    return t;
}
Matrix add(Matrix x, Matrix y, int n) {
    int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            x.t[i][j] = x.t[i][j] + y.t[i][j];
    return x;
}
Matrix Calu_Ak(int k, int n) {
    Matrix x = In, y = A;
    static int i, j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            x.t[i][j] = In.t[i][j], y.t[i][j] = A.t[i][j];
    while(k) {
        if(k&1) x = mult(x, y, n);
        y = mult(y, y, n);
        k /= 2;
    }
    return x;
}

Matrix Calu_total(int n, int k) {
    if(k == 0) return init;
    if(k&1)
        return add(mult(Calu_total(n, k/2), add(In, Calu_Ak(k/2, n), n), n), Calu_Ak(k, n), n);
    else
        return mult(Calu_total(n, k/2), add(In, Calu_Ak(k/2, n), n), n);
}
int main() {
    int n, x, y, i, j, q;
    int cases = 0;
    while(scanf("%d", &n) == 1 && n) {
        vector<int> g[105];
        while(scanf("%d %d", &x, &y) == 2) {
            if(!x && !y)    break;
            g[x].push_back(y);
        }
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                A.t[i][j] = 0, In.t[i][j] = 0,
                init.t[i][j] = 0;
        for(i = 0; i < n; i++) In.t[i][i] = 1;
        printf("Case #%d:\n", ++cases);
        for(i = 1; i <= n; i++) {
            for(j = 0; j < g[i].size(); j++)
                A.t[i-1][g[i][j]-1] += (double)1/g[i].size();
        }
        puts("??");
        res = Calu_total(n, 100);
        for(i = 0; i < n; i++, puts(""))
            for(j = 0; j < n; j++)
            printf("%lf ", res.t[i][j]);
        puts("");
        scanf("%d", &q);
        while(q--) {
            scanf("%d", &x);
        }
    }
    return 0;
}
