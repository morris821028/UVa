#include <bits/stdc++.h>
using namespace std;
/*
	O(K^3 log N)
	The better solution could be found in
	codechef Random Number Generator [https://www.codechef.com/problems/RNG]
	That complexity is O(K log K log N)
*/
const int32_t MOD = 1000000009;
const int MAXK = 100;
struct Matrix {
    int32_t v[MAXK][MAXK];
    int row, col; // row x col
    Matrix(int n, int m, int a = 0) {
        memset(v, 0, sizeof(v));
        row = n, col = m;
        for(int i = 0; i < row && i < col; i++)
            v[i][i] = a;
    }
    Matrix multiply(const Matrix& x, const int32_t mod) const {
        Matrix ret(row, x.col);
        for(int i = 0; i < row; i++) {
            for(int k = 0; k < col; k++) {
                if (!v[i][k])
                    continue;
                for(int j = 0; j < x.col; j++) {
                    ret.v[i][j] += (int64_t) v[i][k]*x.v[k][j]%mod;
                    if (ret.v[i][j] >= mod)
                        ret.v[i][j] -= mod;
                }
            }
        }
        return ret;
    }
    static void uint64_2_binary(int64_t n, char s[]) {
    	if (n == 0) {
    		s[0] = '1', s[1] = '\0';
    		return ;
		}
		int idx = 0;
		while (n) {
			s[idx] = n&1 ? '1' : '0';
			idx++, n >>= 1;
		}
		s[idx] = '\0';
		reverse(s, s+idx);
	}
    Matrix pow(const int64_t &n, const int32_t mod) const {
        Matrix ret(row, col, 1), x = *this;
        Matrix x3 = x.multiply(x, mod);
        x3 = x3.multiply(x, mod);
        char sy[64];
        uint64_2_binary(n, sy);
        
        for (int i = 0; sy[i]; ) {
        	ret = ret.multiply(ret, mod);
        	if (sy[i] == '1' && sy[i+1] == '1') {
        		ret = ret.multiply(ret, mod);
        		ret = ret.multiply(x3, mod);
        		i += 2;
			} else if (sy[i] == '1') {
				ret = ret.multiply(x, mod);
				i++;
			} else if (sy[i+1] == '0') {
				ret = ret.multiply(ret, mod);
				i += 2;
			} else {
				i++;
			}
		}
		return ret;
    }
};

int main() {
	int k;
	int64_t n;
	while (scanf("%d %lld", &k, &n) == 2 && k) {
		Matrix f(k, k, 0);
		for (int i = 0; i < k; i++)
			f.v[0][i] = 1;
		for (int i = 1; i < k; i++)
			f.v[i][i-1] = 1;
		Matrix fn = f.pow(n, MOD);
		int32_t ret = fn.v[0][0];
		printf("%d\n", ret);
	}
	return 0;
}
/*
2 333333336
2 500000000
3 500000000
5 5
3 4
2 3
7 0
0 0
*/
