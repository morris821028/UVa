#include <bits/stdc++.h>
using namespace std;

int D, P, R, B;
int cD[128], cP[128];
vector<int> gD[128], gP[128];
int used[2][128];
void dfs(int u, int flag, int isDSP, int *cnt, int *cost) {
	if (used[isDSP][u])	return ;
	used[isDSP][u] = 1;
	if (isDSP)	*cost += cD[u];
	else		*cost += cP[u];
	if (flag)	(*cnt)++;
	else		(*cnt)--;
	if (isDSP) {
		for (int i = gD[u].size()-1; i >= 0; i--)
			dfs(gD[u][i], !flag, !isDSP, cnt, cost);
	} else {
		for (int i = gP[u].size()-1; i >= 0; i--)
			dfs(gP[u][i], !flag, !isDSP, cnt, cost);
	}
}
int solve(int flag) {
	vector< pair<int, int> > E;
	memset(used, 0, sizeof(used));
	if (flag == 0) {
		for (int i = 0; i < P; i++) {
			if (used[0][i] == 0) {
				int cnt = 0, cost = 0;
				dfs(i, 1, 0, &cnt, &cost);
				E.push_back(make_pair(cnt, cost));
			}
		}
	} else {
		for (int i = 0; i < D; i++) {
			if (used[1][i] == 0) {
				int cnt = 0, cost = 0;
				dfs(i, 1, 1, &cnt, &cost);
				E.push_back(make_pair(cnt, cost));
			}
		}
	}
	
	int dp[32767] = {}, ret = 0;
	dp[0] = 0;
	for (int i = 0; i < E.size(); i++) {
		int a = E[i].first, b = E[i].second;
		for (int j = B; j >= b; j--)
			dp[j] = max(dp[j], dp[j-b]+a);
	}
	for (int i = 0; i <= B; i++)
		ret = max(ret, dp[i]);
	return ret;
} 
int main() {
	while (scanf("%d %d %d %d", &D, &P, &R, &B) == 4) {
		for (int i = 0; i < D; i++)
			scanf("%d", &cD[i]), gD[i].clear();
		for (int i = 0; i < P; i++)
			scanf("%d", &cP[i]), gP[i].clear();
		for (int i = 0; i < R; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			x--, y--;
			gD[x].push_back(y), gP[y].push_back(x);
		}
		
		int ret1 = solve(0) + D;
		int ret2 = solve(1) + P;
		printf("%d %d\n", ret1, ret2);
	}
	return 0;	
}
