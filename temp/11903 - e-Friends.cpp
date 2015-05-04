#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int dp[1<<12][12][12]; // dp[state][last][K] = ways
int main() {
	int testcase, cases = 0;
	int N, K, Q;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &N, &K, &Q);
		int em[16] = {};
		for (int i = 0; i < N; i++) {
			int t, x;
			scanf("%d", &t);
			for (int j = 0; j < t; j++) {
				scanf("%d", &x), x--;
				em[i] |= 1<<x;
			}
		}
		
		vector< pair<int, int> > A;
		for (int i = 0; i < (1<<N); i++)
			A.push_back(make_pair(__builtin_popcount(i), i));
		sort(A.begin(), A.end());
		
		memset(dp, 0, sizeof(dp));
		for (int i = 0; i < N; i++)
			dp[1<<i][i][0] = 1;
			
		for (int p = 0; p < A.size(); p++) {
			int s = A[p].second, t = A[p].first;
			for (int i = 0; i < N; i++) { // last
				for (int j = 0; j < t; j++) { // dissatisfaction index
					if (dp[s][i][j] == 0)
						continue;
//					printf("%d %d %d - %d\n", s, i, j, dp[s][i][j]);
					for (int k = 0; k < N; k++) {
						if ((s>>k)&1)	
							continue;
						int tt = j;
						if ((1<<i)&em[k])	tt++;
						dp[s|(1<<k)][k][tt] += dp[s][i][j];
					}
				}
			}
		}
		
		int preCalc[16] = {};
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				preCalc[j] += dp[(1<<N)-1][i][j];
			}
		}
		
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < Q; i++) {
			int x, ret = 0;
			scanf("%d", &x);
			if (K == 0)	x = N;
			else		x /= K;
			for (int j = 0; j <= x && j <= N; j++)
				ret += preCalc[j];
			printf("%d\n", ret);
		}
	}
	return 0;
}
/*
2

5 50 3
2 2 4
2 1 5
1 1
1 5
1 3
60
10
20

2 10 2
1 2
0
10
5
*/
