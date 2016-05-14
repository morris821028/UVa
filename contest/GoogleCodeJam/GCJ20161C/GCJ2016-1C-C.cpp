#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int J, P, S, K;
		scanf("%d %d %d", &J, &P, &S);
		scanf("%d", &K);
		int ret = 0;
		int g[16][16] = {};
		for (int i = 0; i < P; i++) {
			for (int j = 0; j < K; j++)
				g[i][(i+j)%S] = 1;
			for (int j = 0; j < S; j++)
				ret += g[i][j];
		}

		printf("Case #%d: %d\n", ++cases, ret * J);
		for (int i = 0; i < J; i++) {
			for (int j = 0; j < P; j++) {
				for (int k = 0; k < S; k++) {
					if (g[j][k])
						printf("%d %d %d\n", i+1, j+1, (i+k)%S+1);
				}
			}
		}
	}
	return 0;
}

