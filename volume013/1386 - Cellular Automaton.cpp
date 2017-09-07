#include <bits/stdc++.h>
using namespace std;

const int MAXN = 512;

// multiplication of circulant matrix
static void mul_circulant(int64_t x[], int64_t y[], int n, int m) {
	// y = x * y
	static int64_t z[MAXN];
	memset(z, 0, sizeof(z[0])*n);
	
	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++)
//			z[i] += x[j] * y[(i-j+n)%n];
		for (int j = 0; j <= i; j++)
			z[i] += x[j] * y[i-j];
		for (int j = i+1; j < n; j++)
			z[i] += x[j] * y[i-j+n];
	}
	
	for (int i = 0; i < n; i++)
		y[i] = z[i]%m;
}
int main() {
	int n, m, d, k;
	while (scanf("%d %d %d %d", &n, &m, &d, &k) == 4) {
		static int64_t ret[MAXN];
		static int64_t cM[MAXN]; // circulant matrix
		for (int i = 0; i < n; i++)
			scanf("%lld", &ret[i]);
			
		memset(cM, 0, sizeof(cM));
		cM[0] = 1;
		for (int i = 1; i <= d; i++)
			cM[i] = cM[n-i] = 1;
		
		// divide and conquer
		while (k) {
			if (k&1)
				mul_circulant(cM, ret, n, m);
			mul_circulant(cM, cM, n, m), k >>= 1;
		}
		
		for (int i = 0; i < n; i++)
			printf("%lld%c", ret[i], " \n"[i==n-1]);
	}
	return 0;
}
/*
5 3 1 1
1 2 2 1 2
5 3 1 10
1 2 2 1 2
*/

