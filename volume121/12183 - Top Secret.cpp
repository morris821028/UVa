#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;

// multiplication of circulant matrix
static void mul_circulant(int64_t x[], int64_t y[], int n, int64_t m) {
	// y = x * y
	static int64_t z[MAXN];
	
	for (int i = 0; i < n; i++) {
		int64_t sum = 0;
		for (int j = 0; j <= i; j++)
			sum += x[j] * y[i-j];
		for (int j = i+1; j < n; j++) 
			sum += x[j] * y[i-j+n];
		z[i] = sum;
	}
	
	for (int i = 0; i < n; i++) {
		if (z[i] >= m)	z[i] %= m;
		y[i] = z[i];
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, s, l, r, x;
		int64_t m = 1;
		static int64_t ret[MAXN];
		static int64_t cM[MAXN];	// circulant matrix
		scanf("%d %d %d %d %d", &n, &s, &l, &r, &x);
		for (int i = 0; i < x; i++)
			m = m*10;
		for (int i = 0; i < n; i++) {
			scanf("%lld", &ret[i]);
			ret[i] %= m;
		}
		memset(cM, 0, sizeof(cM[0])*n);
		cM[0] = 1, cM[1] = l, cM[n-1] = r;
		// divide and conquer
		while (s) {
			if (s&1)
				mul_circulant(cM, ret, n, m);
			mul_circulant(cM, cM, n, m), s >>= 1;
		}
		for (int i = 0; i < n; i++)
			printf("%lld%c", ret[i], " \n"[i==n-1]);
	}
	return 0;
}
/*
1
3 0 1 1 1
10 20 30

5
3 1 1 1 3
1 1 1

3 0 1 1 3
23 42 0

3 1 1 1 3
23 42 0

4 10 2 1 9
1 2 3 4

5 999999999 3 8 7
8 7 8 7 12
*/
