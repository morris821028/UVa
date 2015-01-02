#include <stdio.h> 
#include <string.h>

int g[64][64];
int R[4096], nodes[4096];
void deployTree(int k, int n, int e) {
	if (k < n * n / 3) {
		if (R[k] != -1)	k = R[k];
		for (int i = 1; i <= 4; i++)
			deployTree(k * 4 + i, n, e);
	} else {
		g[R[k]/n][R[k]%n] = e;
	}
}
int main() {
	int testcase, cases = 0;
	int n, m, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		memset(R, -1, sizeof(R));
		memset(R, -1, sizeof(nodes));
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			R[x] = y;
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			deployTree(x, n, y);	
		}
		printf("Case %d\n\n", ++cases);
		for (int i = 0; i < n; i++, puts("")) {
			for (int j = 0; j < n; j++)
				printf("%4d", g[i][j]);
		}
		if (testcase)	puts("");
	}
	return 0;
}
