#include <bits/stdc++.h>
using namespace std;

struct Matrix {
    double v[2][2];
    int row, col; // row x col
    Matrix(int n, int m, int a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for(int i = 0; i < row && i < col; i++)
            v[i][i] = a;
    }
    Matrix multiply(const Matrix& x) const {
        Matrix ret(row, x.col);
        for(int i = 0; i < row; i++) {
            for(int k = 0; k < col; k++) {
                if (!v[i][k])
                    continue;
                for(int j = 0; j < x.col; j++) {
                    ret.v[i][j] += v[i][k]*x.v[k][j];
                }
            }
        }
        return ret;
    }
    Matrix pow(const long long& n) const {
        Matrix ret(row, col, 1), x = *this;
        long long y = n;
        while(y) {
            if(y&1)	ret = ret.multiply(x);
            y = y>>1, x = x.multiply(x);
        }
        return ret;
    }
} A(2, 2, 0);

int main() {
	A.v[0][0] = 1, A.v[0][1] = 1;
    A.v[1][0] = 1, A.v[1][1] = 0;
    
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
    	int f0, f1, n;
    	double a, b;
    	scanf("%d %d %lf %lf %d", &f0, &f1, &a, &b, &n);
    	A.v[0][0] = a, A.v[0][1] = b;
    	Matrix ret = A.pow(n);
    	double fn = ret.v[1][0] * f1 + ret.v[1][1] * f0;
    	printf("%.0lf\n", fn);
	}
	return 0;
}
/*
5
0 1 1 1 0
0 1 1 1 1
0 1 1 1 20
0 1 -1 0 1000000000
-1 1 4 -3 18
*/
