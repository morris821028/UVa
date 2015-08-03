#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		int g[64][64];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		int ret = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				ret &= g[i][j] == g[n-i-1][m-j-1];
		}
		puts(ret ? "go forward" : "keep defending");
	}
	return 0;
}
