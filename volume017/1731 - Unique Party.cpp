#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 256;
int f[MAXN][MAXN];
// find the maximum rectangle, 
// satisfy the middle value is large than h
int max_rect(int n, int m, int h) {
	static int8_t c[MAXN][MAXN];
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (f[i][j] >= h)
				c[i][j] = 1;
			else
				c[i][j] = -1;
		}
	}

	int ret = 0;
	static int32_t mx[MAXN];
	for (int i = 0; i < n; i++) {
		int32_t _sum[MAXN] = {};
		int32_t *sum = _sum+1;
		for (int j = i; j < n; j++) {
			int s = 0;
			for (int k = 0; k < m; k++)
				s += c[j][k], sum[k] += s;
			if ((j-i+1)*m <= ret)
				continue;
			mx[m-1] = sum[m-1];
			for (int k = m-2; k >= 0; k--)
				mx[k] = max(mx[k+1], sum[k]);
			int r = 0;
			for (int k = 0; k < m; k++) {
				r = max(r, k);
				while (r+1 < m && mx[r+1] >= sum[k-1])
					r++;
				ret = max(ret, (j-i+1)*(r-k+1));
			}
		}
	}
	return ret;
}

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m, q, h;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				scanf("%d", &f[i][j]);
		}
		scanf("%d", &q);
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
			scanf("%d", &h);
			int ret = max_rect(n, m, h);
			printf("%d\n", ret);
		}
	}
	return 0;
}
/*
1
3  4
6  10  3  1
5  4  2  5
1  7  4  15
2
6  5
*/
