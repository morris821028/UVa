#include <bits/stdc++.h>
using namespace std;

const int MAXS = 131072;
const int MAXN = 512;
const long long LLMAX = 1LL<<60;
char s[MAXS];
int common[MAXN][MAXN];
long long dp[MAXN][MAXN];
int main() {
	int testcase, cases = 0;
	int N, K;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &K);
		vector<string> A;
		
		A.push_back("");
		for (int i = 0; i < N; i++) {
			scanf("%s", s);
			A.push_back(s);
		}
		
		sort(A.begin(), A.end());
		N = A.size();
		for (int i = 0; i < N; i++) {
			for (int j = i+1; j < N; j++) {
				int cnt = 0, x = i, y = j;
				for (int k = 0; k < A[x].length() && k < A[y].length(); k++) {
					if (A[x][k] != A[y][k])
						break;
					cnt++;
				}
				common[i][j] = common[j][i] = cnt;
			}
		}
		
		for (int i = 0; i <= N; i++) {
			for (int j = 0; j <= K; j++)
				dp[i][j] = LLMAX;
		}
		dp[0][0] = 0;
//		for (int i = 0; i < N; i++)
//			printf("%s\n", A[i].c_str());
			
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < K; j++) {
				if (dp[i][j] == LLMAX)
					continue;
				for (int k = i+1; k < N; k++) {
					long long t = 0;
					t += A[k].length() - common[i][k];
					t += A[i].length() - common[i][k];
					dp[k][j+1] = min(dp[k][j+1], dp[i][j] + t);
				}
//				printf("%d %d - %lld\n", i, j, dp[i][j]);
			}
		}
		
		long long ret = LLMAX;
		for (int i = 0; i < N; i++)
			ret = min(ret, dp[i][K] + (long long) A[i].length());
		printf("Case #%d: %lld\n", ++cases, ret+K);
	}
	return 0;
}
/*
5
6 3
a
hair
box
awesome
hailzzzzz
haz
*/

