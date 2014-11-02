#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int R[256][128], L[256][128];
int dp[256][128];
int main() {
	int cases = 0;
	int N, T, t[128];
	int M1, M2, d;
	while (scanf("%d", &N) == 1 && N) {
		int time[128] = {};
		memset(R, 0, sizeof(R));
		memset(L, 0, sizeof(L));
		scanf("%d", &T);
		for (int i = 1; i < N; i++)
			scanf("%d", &t[i]);
		for (int i = 1; i < N; i++)
			time[i + 1] = time[i] + t[i];
		scanf("%d", &M1);
		for (int i = 0; i < M1; i++) {
			scanf("%d", &d);
			R[d][1] = 1;
			for (int i = 2; i <= N && d + time[i] <= T; i++)
				R[d + time[i]][i] = 1;
		}
		scanf("%d", &M2);
		for (int i = 0; i < M2; i++) {
			scanf("%d", &d);
			L[d][N] = 1;
			for (int i = N - 1; i >= 1 && d + time[N] - time[i] <= T; i--)
				L[d + time[N] - time[i]][i] = 1;
		}
		printf("Case Number %d: ", ++cases);
		
		memset(dp, 63, sizeof(dp));
		int INF = dp[0][0];
		dp[0][1] = 0;
		for (int i = 0; i <= T; i++) {
			for (int j = 1; j <= N; j++) {
				dp[i+1][j] = min(dp[i+1][j], dp[i][j] + 1);
				if (j + 1 <= N && R[i][j] && i + t[j] <= T)
					dp[i + t[j]][j+1] = min(dp[i + t[j]][j+1], dp[i][j]);
				if (j - 1 >= 1 && L[i][j] && i + t[j-1] <= T)
					dp[i + t[j-1]][j-1] = min(dp[i + t[j-1]][j-1], dp[i][j]);
			}
		}
		if (dp[T][N] != INF)
			printf("%d\n", dp[T][N]);
		else
			puts("impossible");
	}
	return 0;
}
