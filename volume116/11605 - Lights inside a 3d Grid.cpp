#include <stdio.h> 
#include <string.h>
struct Matrix {
	double v[2][2];
	int row, col; // row x col
	Matrix(int n, int m, double a = 0) {
		memset(v, 0, sizeof(v));
		row = n, col = m;
		for(int i = 0; i < row && i < col; i++)
			v[i][i] = a;
	}
	Matrix operator*(const Matrix& x) const {
		Matrix ret(row, x.col);
		for(int i = 0; i < row; i++)
			for(int j = 0; j < x.col; j++)
				for(int k = 0; k < col; k++)
					ret.v[i][j] += v[i][k] * x.v[k][j];
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
};

int main() {
	int N, M, P, K;
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d %d", &N, &M, &P, &K);
		double pN[128], pM[128], pP[128];
		for(int i = 1; i <= N; i++)
			pN[i] = (i * (N-i+1) * 2 - 1) / (double)(N * N);			
		for(int i = 1; i <= M; i++)
			pM[i] = (i * (M-i+1) * 2 - 1) / (double)(M * M);
		for(int i = 1; i <= P; i++)
			pP[i] = (i * (P-i+1) * 2 - 1) / (double)(P * P);
		double ret = 0;
		for(int i = 1; i <= N; i++) {
			for(int j = 1; j <= M; j++) {
				for(int k = 1; k <= P; k++) {
					double p = pN[i] * pM[j] * pP[k];
					Matrix mm(2, 2);
					mm.v[0][0] = mm.v[1][1] = 1 - p;
					mm.v[0][1] = mm.v[1][0] = p;
					Matrix mmk = mm ^ K;
					ret += mmk.v[0][1];
				}
			}
		}
		printf("Case %d: %.10lf\n", ++cases, ret);
	}
	return 0;
}
