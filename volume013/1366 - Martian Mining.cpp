#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 512;
int Y[MAXN][MAXN] = {}, B[MAXN][MAXN] = {};
int dp[MAXN][MAXN] = {};
int main() {
	int N, M;
	while (scanf("%d %d", &N, &M) == 2 && N) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				scanf("%d", &Y[i][j]);
				Y[i][j] += Y[i][j-1];
			}
		}
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				scanf("%d", &B[i][j]);
				B[i][j] += B[i-1][j];
			}
		}
		
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				int val = 0;
				val = max(val, dp[i-1][j] + Y[i][j]);
				val = max(val, dp[i][j-1] + B[i][j]);
				dp[i][j] = val;
			}
		}
		printf("%d\n", dp[N][M]);
	}
	return 0;
}
/*
4 4
0 0 10 9
1 3 10 0
4 2 1 3 
1 1 20 0
10 0 0 0
1 1 1 30
0 0 5 5
5 10 10 10
0 0
*/
