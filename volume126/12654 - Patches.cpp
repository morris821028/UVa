#include <stdio.h>
#include <algorithm>
using namespace std;

int F[1024];
int main() {
	int N, C, T[2];
	while(scanf("%d %d %d %d", &N, &C, &T[0], &T[1]) == 4) {
		for(int i = 0; i < N; i++)
			scanf("%d", &F[i]);
		sort(F, F+N);
		int ret = 0x3f3f3f3f;
		for(int i = 0; i < N; i++) {
			int dp[1024] = {};
			for(int j = 0; j <= N; j++)
				dp[j] = 0x3f3f3f3f;
			dp[0] = 0;
			int cover1 = 0, cover2 = 0;
			for(int j = 0; j < N; j++) {
				while(cover1 + 1 < N && F[cover1 + 1] - F[j] <= T[0])
					cover1++;
				while(cover2 + 1 < N && F[cover2 + 1] - F[j] <= T[1])
					cover2++;
				dp[cover1+1] = min(dp[cover1+1], dp[j] + T[0]);
				dp[cover2+1] = min(dp[cover2+1], dp[j] + T[1]);
			}
			ret = min(ret, dp[N]);
			swap(F[0], F[N]);
			F[N] += C;
			for(int j = 0; j < N; j++)
				F[j] = F[j+1];
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
5 20 2 3
2 5 8 11 15
4 20 12 9
1 2 3 13
2 10 3 2
0 9
2 10 3 2
0 2
2 10 3 2
0 3
*/
