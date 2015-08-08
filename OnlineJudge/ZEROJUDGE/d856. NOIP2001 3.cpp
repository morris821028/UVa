#include <bits/stdc++.h> 
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, p, K;
		char s[1024];
		string A = "", word[1024];
		scanf("%d %d", &p, &K);
		for (int i = 0; i < p; i++)
			scanf("%s", s), A = A + s;
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", s), word[i] = s;
		
		int cost[305][305] = {}, match[305];
		for (int i = 0; i < A.length(); i++) {
			match[i] = INT_MAX;
			for (int j = 0; j < n; j++) {
				if (i+word[j].length()-1 >= A.length())
					continue;
				int m = 1;
				for (int k = 0; k < word[j].length() && m; k++)
					m &= word[j][k] == A[i+k];
				if (m)
					match[i] = min(match[i], (int) (i+word[j].length()-1));
			}
		}
		for (int i = 0; i < A.length(); i++) {
			for (int j = i; j < A.length(); j++) {
				int val = 0;
				for (int k = i; k <= j; k++) {
					if (match[k] <= j)	val++;
				}
				cost[i][j] = val;
			}
		}
		
		int dp[305][305] = {};
		for (int i = 0; i < A.length(); i++)
			dp[i][1] = cost[0][i];
		for (int i = 1; i < A.length(); i++) {
			for (int j = 2; j <= K; j++) {
				for (int k = i; k >= j-1; k--)
					dp[i][j] = max(dp[i][j], dp[k-1][j-1] + cost[k][i]);
			}
		}
		printf("%d\n", dp[A.length()-1][K]);
	}
	return 0;
}
