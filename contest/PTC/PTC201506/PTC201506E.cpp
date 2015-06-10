#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 205; 
struct Matrix {
    int v[MAXN][MAXN];
    int row, col; // row x col
    Matrix(int n, int m, int a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                v[i][j] = 0;
        for (int i = 0; i < row && i < col; i++)
            v[i][i] = a;
    }
    Matrix operator*(const Matrix& x) const {
        Matrix ret(row, x.col);
        for (int i = 0; i < row; i++) {
            for (int k = 0; k < col; k++) {
            	if (v[i][k])
                for(int j = 0; j < x.col; j++) {
                	if (x.v[k][j])
//                        ret.v[i][j] = ret.v[i][j] + v[i][k] * x.v[k][j];
                	ret.v[i][j] = max(ret.v[i][j], v[i][k] + x.v[k][j]);
                }
            }
        }
        return ret;
    }
    Matrix operator+(const Matrix& x) const {
        Matrix ret(row, col, 0);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                ret.v[i][j] = v[i][j] + x.v[i][j];
            }
        }
        return ret;
    }
    Matrix operator^(const int& n) const {
//        Matrix ret(row, col, 1), x = *this;
		Matrix ret(row, col, 0), x = *this;
        int y = n;
        y--, ret = x; // this problem need,
        while (y) {
            if (y&1)	ret = ret * x;
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
    int testcase;
    scanf("%d", &testcase);
    while (testcase--) {
    	int N, M, K, Q;
    	scanf("%d %d %d %d", &N, &M, &K, &Q);
    	Matrix A(N, N, 0);
    	for (int i = 0; i < M; i++) {
    		int u, v, w;
    		scanf("%d %d %d", &u, &v, &w);
    		u--, v--;
    		A.v[u][v] = max(A.v[u][v], w);
    	}
    	A = A^K;
    	for (int i = 0; i < Q; i++) {
    		int u, v;
    		scanf("%d %d", &u, &v);
    		u--, v--;
    		printf("%d\n", A.v[u][v]);
    	}
    }
    return 0;
}
/*
2
3 3 2 3
1 2 3
2 3 4
3 1 2
1 2
2 1
1 3

3 4 10 2
1 2 1000
2 3 100
3 1 10
1 3 1
2 2
3 2
*/
