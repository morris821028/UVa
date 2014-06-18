#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
#define MOD 1000000007
struct Matrix {
	int row, column;
	long long v[30][30];
	Matrix(int single, int r, int c) {
		memset(v, 0, sizeof(v));
		for(int i = 0; i < r && i < c; i++)
			v[i][i] = single;
		row = r, column = c;
	}
	void print() {
		for(int i = 0; i < row; i++) {
			printf("[");
			for(int j = 0; j < column; j++) {
				printf("%3d", v[i][j]);
			}
			puts("]");
		}
		puts("--");
	}
};
Matrix multiply(Matrix &x, Matrix &y) {
	Matrix ret(0, x.row, y.column);// x.column == y.row
	for(int i = 0; i < x.row; i++) {
		for(int j = 0; j < y.column; j++)
			for(int k = 0; k < x.column; k++) {
				ret.v[i][j] += x.v[i][k] * y.v[k][j];
				ret.v[i][j] %= MOD;
			}
	}
	return ret;
}
Matrix matrix_pow(Matrix x, int n) {
	Matrix ret(1, x.row, x.column);
	while(n) {
		if(n&1)
			ret = multiply(ret, x);
		x = multiply(x, x), n >>= 1;
	}
	return ret;
}
int level[30], g[30][30];
void buildLevelGraph(int N, int s) {
	memset(level, 0, sizeof(level));
	queue<int> Q;
	Q.push(s), level[s] = 1;
	while(!Q.empty()) {
		int tn = Q.front();
		Q.pop();
		for(int i = 0; i < N; i++) {
			if(g[tn][i] && level[i] == 0) {
				level[i] = level[tn] + 1;
				Q.push(i);
			}
		}
	}
}
int main() {
	int testcase, cases = 0;
	int N, M, K, D; 
	int i, j, k, x, y;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d %d", &N, &M, &K, &D);
		memset(g, 0, sizeof(g));
		for(i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			g[x][y] = g[y][x] = 1;
		}
		buildLevelGraph(N, K);
		Matrix odd(1, N, N), even(1, N, N);
		for(i = 0; i < N; i++) {
			for(j = 0; j < N; j++) {
				if(level[i]&1)
					even.v[i][j] |= g[i][j];
				else
					odd.v[i][j] |= g[i][j];
			}
		}
		Matrix oe = multiply(even, odd);
		Matrix ret = matrix_pow(oe, D/2);
		if(D&1)
			ret = multiply(odd, ret);
		printf("Case %d:", ++cases);
		for(i = 0; i < N; i++)
			printf(" %lld", ret.v[i][K]);
		puts("");
	}
	return 0;
}
