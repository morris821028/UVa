#include <bits/stdc++.h>
using namespace std;
int C, S;
int G[3][1000];
long long ret = 0;
const long long MOD = 1e+9 + 9;
int U[1000];
int check(int x, int y) {
	if (x == 1)	return 1;
	if (x == 0) {
		for (int d = 1; y-d-d >= 0; d++) {
			if (G[0][y] + G[1][y-d] + G[2][y-d-d] != S)
				return 0;
		}
	} else {
		for (int d = 1; y-d-d >= 0; d++) {
			if (G[2][y] + G[1][y-d] + G[0][y-d-d] != S)
				return 0;
		}
	}
	return 1;
}
void dfs(int x, int y) {
	if (x == 3) {
		if (U[y] != S)
			return ;
		y++, x = 0;
	}
	if (y == C) {
//		for (int i = 0; i < 3; i++) {
//			for (int j = 0; j < C; j++)
//				printf("%d", G[i][j]);
//			puts("");
//		}
//		puts("----");
		ret ++;
		ret %= MOD;
		return ;
	}
	for (int i = x == 2 ? S - U[y] : 0; i+U[y] <= S; i++) {
		U[y] += i;
		G[x][y] = i;
		if (check(x, y))
			dfs(x+1, y);
		U[y] -= i;
	}
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &C, &S);
		ret = 0;
		dfs(0, 0);
		printf("%lld\n", ret);
		fprintf(stderr, "Case #%d %lld\n", ++cases, ret);
		fflush(stderr);
	}
	return 0;
}

