#include <stdio.h> 
#include <string.h>
const unsigned long long mod = 1000000007ULL;	
unsigned long long mul(unsigned long long a, unsigned long long b) { 
	unsigned long long ret = 0; 
	for( ; b != 0; b>>=1, (a<<=1)%=mod) 
		if(b&1) (ret += a) %= mod; 
	return ret; 
}
struct Matrix {
	unsigned long long v[4][4];
	int row, col; // row x col

	Matrix(int n, int m, unsigned long long a = 0) {
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
					ret.v[i][j] = (ret.v[i][j] + mul(v[i][k], x.v[k][j]))%mod;
				}
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
	void print() {
		for (int i = 0; i < row; i++) {
			printf("[");
			for (int j = 0; j < col; j++) {
				printf("%5llu%c", v[i][j], j == col - 1 ? ']' : ',');
			}
			puts("");
		}
	}
};
int main() {
	int N, M, K;
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout); 
	while (scanf("%d %d %d", &N, &M, &K) == 3) {
		int state = 2; // dir : (left, right), (up, down)
		Matrix m(state, state), a(state, 1);
		m.v[0][0] = 0, m.v[0][1] = M - 1;
		m.v[1][0] = N - 1, m.v[1][1] = 0;
		a.v[0][0] = mul(mul(N, M), (M - 1));
		a.v[1][0] = mul(mul(N, M), (N - 1));
		Matrix v = (m ^ K) * a;
//		v.print();
		unsigned long long ret = 0;
		for (int i = 0; i < v.row; i++) {
			for (int j = 0; j < v.col; j++) {
				ret = (ret + v.v[i][j])%mod;
			}
		}
		printf("%llu\n", ret);
	}
	return 0;
}
/*
2 2 1
2 2 100 
2 3 1 
2 3 2

8
8
24
36

1 5 31
1 3 15
2 1 93
1 5 52
4 5 24
4 5 97
4 2 34
1 2 16
4 2 57
1 1 100


*/
