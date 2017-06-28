#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 512;
static int W[MAXN][MAXN], D[MAXN];

int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				scanf("%d", &W[i][j]);
		}
		for (int i = 0; i < n; i++)
			scanf("%d", &D[i]);
		
		int64_t ret = 0;
		for (int i = n-1; i >= 0; i--) {
			int x = D[i];
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++)
					W[j][k] = min(W[j][k], W[j][x]+W[x][k]);
			}
			
			int64_t tmp = 0;
			for (int j = i; j < n; j++) {
				int u = D[j];
				for (int k = j+1; k < n; k++) {
					int v = D[k];
					tmp += W[u][v] + W[v][u];
				}
			}
			ret = ret + tmp;
		}
		
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3
3
0  35  58
12  0  5
1  2  0
0  1  2
3
0  9982  1413
8327  0  5612
3577  7893  0
1  0  2
4
0  50  10  30
4  0  23  58
2  1  0  5
67  24  25  0
0  3  1  2
*/
