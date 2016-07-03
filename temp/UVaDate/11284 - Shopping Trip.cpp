#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 64;
int main() {
	int testcase;
	int N, M, P;
	int u, v, a, b;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &N, &M);
		
		int g[MAXN][MAXN], profit[MAXN] = {};
		int dp[1<<12][12];
		memset(g, 0x3f, sizeof(g));
		for (int i = 0; i < M; i++) {
			scanf("%d %d %d.%d", &u, &v, &a, &b);
			g[u][v] = min(g[u][v], a * 100 + b);
			g[v][u] = min(g[v][u], a * 100 + b);
		}
		
		scanf("%d", &P);		
		for (int i = 0; i < P; i++) {
			scanf("%d %d.%d", &u, &a, &b);
			profit[u] += a * 100 + b;
		}
		
		// floyd algorithm
		for (int i = 0; i <= N; i++)
			g[i][i] = 0;
		for (int k = 0; k <= N; k++)
			for (int i = 0; i <= N; i++) 
				for (int j = 0; j <= N; j++)
					g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
					
		// get store
		vector<int> S;
		for (int i = 0; i <= N; i++) {
			if (profit[i] > 0)
				S.push_back(i);
		}
		
		// run dp
		vector< pair<int, int> > o;
		for (int i = 0; i < (1<<S.size()); i++) {
			for (int j = 0; j < S.size(); j++)
				dp[i][j] = -0x3f3f3f3f;
			o.push_back(make_pair(__builtin_popcount(i), i));
		}
				
		int ret = -0x3f3f3f3f;
		for (int i = 0; i < S.size(); i++) {
			u = S[i];
			dp[1<<i][i] = -g[0][u] + profit[u];
		}
		
		sort(o.begin(), o.end());
		for (int i = 0; i < o.size(); i++) {
			int state = o[i].second;
			for (int j = 0; j < S.size(); j++) {
				if (dp[state][j] == -0x3f3f3f3f)
					continue;
					
				u = S[j];
				ret = max(ret, dp[state][j] - g[u][0]);
				for (int k = 0; k < S.size(); k++) {
					if ((state>>k)&1)
						continue;
					v = S[k];
					dp[state|(1<<k)][k] = max(dp[state|(1<<k)][k], dp[state][j] - g[u][v] + profit[v]);
				}
			}
		}
		
		if (ret > 0)
			printf("Daniel can save $%d.%02d\n", ret/100, ret%100);
		else
			printf("Don't leave the house\n");
	}
	return 0;
}
