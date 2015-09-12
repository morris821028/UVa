#include <bits/stdc++.h>
using namespace std;
const long long mod = 100000007;
struct Matrix {
    long long v[2][2];
    int row, col; // row x col
    Matrix(int n, int m, int a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for(int i = 0; i < row && i < col; i++)
            v[i][i] = a;
    }
    Matrix multiply(const Matrix& x, const long long mod) const {
        Matrix ret(row, x.col);
        for(int i = 0; i < row; i++) {
            for(int k = 0; k < col; k++) {
                if (!v[i][k])
                    continue;
                for(int j = 0; j < x.col; j++) {
                    ret.v[i][j] += v[i][k] * x.v[k][j] % mod;
                    if (ret.v[i][j] >= mod)
                        ret.v[i][j] -= mod;
                }
            }
        }
        return ret;
    }
    Matrix pow(const long long& n, const long long mod) const {
        Matrix ret(row, col, 1), x = *this;
        long long y = n;
        while(y) {
            if(y&1)	ret = ret.multiply(x, mod);
            y = y>>1, x = x.multiply(x, mod);
        }
        return ret;
    }
} FibA(2, 2, 0);

int main() {
    FibA.v[0][0] = 1, FibA.v[0][1] = 1;
    FibA.v[1][0] = 1, FibA.v[1][1] = 0;
    long long m, f, k;
    while (scanf("%lld %lld %lld", &m, &f, &k) == 3) {
        Matrix A = FibA.pow(k+1, mod);
        long long ret = (A.v[0][0] * f + A.v[1][0] * m)%mod;
        printf("%lld\n", ret);
    }
    return 0;
}