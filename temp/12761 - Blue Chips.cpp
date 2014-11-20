#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;

int mod = 10000;
struct Matrix {
    int v[64][64];
    int row, col; // row x col
    Matrix(int n, int m, int a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for(int i = 0; i < row && i < col; i++)
            v[i][i] = a;
    }
    Matrix operator*(const Matrix& x) const {
        Matrix ret(row, x.col);
        for(int i = 0; i < row; i++) {
            for(int k = 0; k < col; k++) {
                if (v[i][k])
                    for(int j = 0; j < x.col; j++) {
                        ret.v[i][j] += v[i][k] * x.v[k][j],
                        ret.v[i][j] %= mod;
                    }
            }
        }
        return ret;
    }
    Matrix operator+(const Matrix& x) const {
        Matrix ret(row, col);
        for(int i = 0; i < row; i++) {
            for(int j = 0; j < col; j++) {
                ret.v[i][j] = v[i][j] + x.v[i][j];
            }
        }
        return ret;
    }
    Matrix operator^(const int& n) const {
        Matrix ret(row, col, 1), x = *this;
        int y = n;
        while(y) {
            if(y&1)	ret = ret * x;
            y = y>>1, x = x * x;
        }
        return ret;
    }
    Matrix powsum(int k) {
        if (k == 0) return Matrix(row, col, 0);
        Matrix vv = powsum(k/2);
        if (k&1) {
            return vv * (Matrix(row, col, 1) + vv) + vv;
        } else {
            return vv * (Matrix(row, col, 1) + vv);
        }
    }
};
int main() {	
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout); 
    int testcase, N, K, D;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d %d", &N, &K, &D);
        mod = N;
        Matrix m(N, N), a(N, 1);
        for (int i = 0; i < N; i++)
            scanf("%d", &a.v[i][0]), a.v[i][0] %= N;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if ((abs(i - j) <= D || N - abs(i - j) <= D) && i != j)
                    m.v[i][j] = 1;
            }
        }
        Matrix ret = (m ^ K);
        ret = ret * a;
        int mn = 0x3f3f3f3f;
        for (int i = 0; i < N; i++) {
            mn = min(mn, ret.v[i][0]);
        }
        printf("%d\n", mn);
        int f = 0;
        for (int i = 0; i < N; i++) {
            if (ret.v[i][0] == mn) {
                if (f)  putchar(' ');
                f = 1;
                printf("%d", i + 1);
            }
        }
        puts("");
    }
    return 0;
}
/*
 1
 3 3 1
 1 2 2

 */
