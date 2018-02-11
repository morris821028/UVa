#include <bits/stdc++.h>
using namespace std;
const int64_t MOD = 73405LL;
const int MAXM = 120;
/*
	record last m position, the shift value(A[i]-i) is between -m and +m.
	then, add a new (n+1)-th number into permutation, get the shift
	status of last m positions.

	If K = 2, the possible shift values for last one are -2, -1, 0.
	The possible shift values for second-last one are -2, -1, 0, 1.
*/
struct Matrix {
	int64_t v[MAXM*MAXM];
	int n;
#define pos(x, y) ((x)*n+(y))
	Matrix(int t = 0, int n = 1) {
		memset(v, 0, sizeof(v));
		this->n = n;
		for (int i = 0; i < n; i++)
			v[pos(i, i)] = t;
	}
	Matrix operator*(const Matrix &y) const {
		Matrix ret(0, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (v[pos(i, j)])
				for (int k = 0; k < n; k++) {
					ret.v[pos(i, k)] += v[pos(i, j)] * y.v[pos(j, k)] % MOD;
					if (ret.v[pos(i, k)] >= MOD)
						ret.v[pos(i, k)] %= MOD;
				}
			}
		}
		return ret;
	}
	Matrix pow(int y) {
		Matrix ret(1, n), x = *this;
		while (y) {
			if (y&1)
				ret = ret * x;
			x = x*x, y >>= 1;
		}
		return ret;
	} 
#undef pos 
};
int place(int u, int pos, int n) {
	int p[4];
	for (int i = n-1; i >= 0; i--)
		p[i] = u%(2*n-i)-n, u /= 2*n-i;
	for (int i = n; i > pos; i--) {
		p[i] = p[i-1]-1;
		if (abs(p[i]) > n)
			return -1;
	}
	p[pos] = n - pos;
	assert(abs(p[pos]) <= n);
	int v = 0;
	for (int i = 1; i <= n; i++)
		v = v*(2*n-(i-1)) + p[i] + n;
	return v;
}
Matrix mtx[3];
int build() {
	mtx[0].n = 2, mtx[1].n = 12, mtx[2].n = 120;
	for (int i = 0; i < 2; i++) {
		int n = 2;
		for (int j = 0; j < 2; j++) {
			int t = place(i, j, 1);
			if (t >= 0)
				mtx[0].v[i*n+t] = 1;
		}
	}
	for (int i = 0; i < 12; i++) {
		int n = 12;
		for (int j = 0; j < 3; j++) {
			int t = place(i, j, 2);
			if (t >= 0)
				mtx[1].v[i*n+t] = 1;
		}
	}
	for (int i = 0; i < 120; i++) {
		int n = 120;
		for (int j = 0; j < 4; j++) {
			int t = place(i, j, 3);
			if (t >= 0)
				mtx[2].v[i*n+t] = 1;
		}
	}
}
int brute(int n, int k) {
	int A[8], ret = 0;
	for (int i = 0; i < n; i++)
		A[i] = i;
	do {
		int valid = 1;
		for (int i = 0; i < n && valid; i++)
			valid &= abs(A[i]-i) <= k;
		ret += valid;
	} while (next_permutation(A, A+n));
	return ret;
}
int64_t solve(int n, int k) {
	// assert n > k
	int A[8];
	int64_t val[MAXM] = {};	// initial status
	for (int i = 0; i < k; i++)
		A[i] = i;
	do {
		int valid = 1;
		for (int i = 0; i < k && valid; i++)
			valid &= abs(A[i]-i) <= k;
		if (valid) {
			int u = 0;
			for (int i = 0; i < k; i++)
				u = u * (2*k-i) + (A[i]-i+k);
			val[u]++;
		}
	} while (next_permutation(A, A+k));
	// add (n-k) numbers
	const int status[] = {2, 12, 120};
	int y = n-k, m = status[k-1];
	Matrix x = mtx[k-1];
	while (y) {
		if (y&1) {
			int64_t tmp[MAXM] = {};
			for (int i = 0; i < m; i++) {
				if (val[i] == 0)
					continue;
				for (int j = 0; j < m; j++) {
					tmp[j] += val[i]*x.v[i*m+j]%MOD;
					if (tmp[j] >= MOD)
						tmp[j] %= MOD;
				}
			}
			for (int i = 0; i < m; i++)
				val[i] = tmp[i];
		}
		y >>= 1, x = x*x;
	}
	int64_t ret = 0;
	for (int i = 0; i < m; i++)
		ret = ret + val[i];
	ret %= MOD;
	return ret;
}
int main() {
	build();
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, k;
		scanf("%d %d", &n, &k);
		printf("Case %d: ", ++cases);
		if (k == 0) {
			puts("1");
			continue;
		}
		if (n <= k) {
			int ret = brute(n, k);
			printf("%d\n", ret);
			continue;
		}
		int64_t ret = solve(n, k);
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3
4 2
100 0
10 1
*/
