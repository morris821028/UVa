#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

class BigInteger {
public:
    vector<long long> v;
    long long MAXC;
    BigInteger(int x = 0) {
        v = vector<long long>(10, 0);
        v[0] = x;
        MAXC = 100000000;
        normal();
    }
    BigInteger operator+(const BigInteger &x) const {
        BigInteger r(0);
        r.v.resize(max(v.size(), x.v.size()) + 2, 0);
        for (int i = 0; i < v.size(); i++)
            r.v[i] += v[i];
        for (int i = 0; i < x.v.size(); i++)
            r.v[i] += x.v[i];
        r.normal();
        return r;
    }
    BigInteger operator*(const BigInteger &x) const {
        BigInteger r(0);
        r.v.resize(v.size() + x.v.size() + 2, 0);
        for (int i = 0; i < v.size(); i++) {
            if (v[i] == 0)
                continue;
            for (int j = 0; j < x.v.size(); j++)
                r.v[i+j] += v[i] * x.v[j];
        }
        r.normal();
        return r;
    }
    void normal() {
        for (int i = 0; i < v.size(); i++) {
            if (v[i] >= MAXC) {
                v[i+1] += v[i] / MAXC;
                v[i] %= MAXC;
            }
        }
        int s = (int) v.size() - 1;
        while (s > 0 && v[s] == 0)
            s--;
        v.resize(s+1);
    }
    bool isZero() const {
        if (v.size() > 1)   return false;
        return v[0] == 0;
    }
    void print() {
        printf("%lld", v[v.size()-1]);
        for (int i = (int) v.size() - 2; i >= 0; i--)
            printf("%08lld", v[i]);
        puts("");
    }
};

struct Matrix {
    BigInteger v[2][2];
    int row, col; // row x col
    Matrix(int n, int m, int a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                v[i][j] = BigInteger(0);
        for (int i = 0; i < row && i < col; i++)
            v[i][i] = BigInteger(a);
    }
    Matrix operator*(const Matrix& x) const {
        Matrix ret(row, x.col);
        for (int i = 0; i < row; i++) {
            for (int k = 0; k < col; k++) {
                if (!v[i][k].isZero()) {
                    for(int j = 0; j < x.col; j++) {
                        ret.v[i][j] = ret.v[i][j] + v[i][k] * x.v[k][j];
                    }
                }
            }
        }
        return ret;
    }
    Matrix operator+(const Matrix& x) const {
        Matrix ret(row, col);
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                ret.v[i][j] = v[i][j] + x.v[i][j];
            }
        }
        return ret;
    }
    Matrix operator^(const int& n) const {
        Matrix ret(row, col, 1), x = *this;
        int y = n;
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
    int testcase, A, B, m;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d %d %d", &A, &B, &m);
        Matrix X(2, 2), Y(1, 1), Z(2, 1);
        X.v[0][0] = BigInteger(0);
        X.v[0][1] = BigInteger(1);
        X.v[1][0] = BigInteger(1);
        X.v[1][1] = BigInteger(1);
        Y = X^m;
        Z.v[0][0] = BigInteger(A);
        Z.v[1][0] = BigInteger(B);
        Y = Y * Z;
        Y.v[0][0].print();
//        long long f1 = A, f2 = B;
//        for (int i = 0; i < m; i++) {
//            long long f = f1 + f2;
//            f1 = f2, f2 = f;
//        }
//        printf("%lld\n", f1);
    }
    return 0;
}
/*
 999
 123 456 0
 100 100 50
 0 0 10
 0 1 10
 999999 1000000 0
 999999 1000000 1
 999999 1000000 2
 999999 1000000 10
 999999 1000000 16
 999999 1000000 18
 20 122 40
 
 0 1 10000
 0 1 100000
 2 0 1 
*/
