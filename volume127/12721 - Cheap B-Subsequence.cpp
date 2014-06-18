#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;

int dp[128][128], cost[26][128];
int main() {
	int testcase, cases = 0;
	char S[128];
	int B, P, C, N, M;
	scanf("%d", &testcase);
	while(testcase--) {		
		scanf("%s %d", S+1, &B);
		
		N = strlen(S+1);
		memset(dp, 0x3f, sizeof(dp));
		memset(cost, 0, sizeof(cost));
		
		for(int i = 0; i < 26; i++) {
			scanf("%d", &M);
			for(int j = 0; j < M; j++) {
				scanf("%d %d", &P, &C);
				int oP = P;
				while(oP <= N)
					cost[i][oP] += oP / P * C, oP += P;
			}
		}		

		dp[0][0] = 0;
		for(int i = 0; i < B; i++) {
			for(int j = 0; j <= N; j++) {
				for(int k = j + 1; k <= N; k++) {
					int c = cost[S[k] - 'a'][i + 1];
					dp[i+1][k] = min(dp[i+1][k], dp[i][j] + c);
				}
			}
		}
		int ret = 0x3f3f3f3f;
		for(int i = 1; i <= N; i++)
			ret = min(ret, dp[B][i]);
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
2
abcd 1
1 1 20
1 1 15
1 1 8
1 1 30
1 1 2
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0

abaabcbc 4
2 2 3 4 10
2 1 4 7 50
2 1 2 4 20
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0
0

*/
