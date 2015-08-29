#include <bits/stdc++.h>
using namespace std;

int n, m;
int goal[128], EXP[128], board[8][8];
vector<int> var[128];
set<int> COL[128], ROW[128];
int used[128][128] = {};
int test() {
	int ok = 1;
	for (int i = 0; i < m; i++) {
		if (EXP[i] == '+') {
			int sum = 0, f = 0;
			for (int j = 0; j < var[i].size(); j++) {
				int x = var[i][j] - 1;
				if (!used[x/n][x%n]) {
					f = 1;
					break;
				}
				sum += board[x/n][x%n];
			}
			if (f)	continue;
			ok = sum == goal[i];
		} else if (EXP[i] == 'x') {
			int sum = 1, f = 0;
			for (int j = 0; j < var[i].size(); j++) {
				int x = var[i][j] - 1;
				if (!used[x/n][x%n]) {
					f = 1;
					break;
				}
				sum *= board[x/n][x%n];
			}
			if (f)	continue;
			ok = sum == goal[i];
		} else if (EXP[i] == '-') {
			int x = var[i][0] - 1, y = var[i][1] - 1;
			if (!used[x/n][x%n] || !used[y/n][y%n])
				continue;
			ok = 0;
			x = board[x/n][x%n], y = board[y/n][y%n];
			if (x - y == goal[i] || y - x == goal[i])
				ok = 1;
		} else if (EXP[i] == '/') {
			int x = var[i][0] - 1, y = var[i][1] - 1;
			if (!used[x/n][x%n] || !used[y/n][y%n])
				continue;
			ok = 0;
			x = board[x/n][x%n], y = board[y/n][y%n];
			if (x && y % x == 0 && y / x == goal[i])
				ok = 1;
			swap(x, y);
			if (x && y % x == 0 && y / x == goal[i])
				ok = 1;
		}
		if (!ok)	return 0;
	}
	return 1;
}
vector< pair<int, int> > order;
int dfs(int idx) {
	if (!test())
		return 0;
	if (idx == order.size()) {
		if (test()) {
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					printf("%d%c", board[i][j], j == n-1 ? '\n' : ' ');
			return 1;
		}
		return 0;
	}
	int x = order[idx].first, y = order[idx].second;
	
	for (int i = 1; i <= n; i++) {
		if (COL[x].count(i) || ROW[y].count(i))
			continue;
		COL[x].insert(i), ROW[y].insert(i);
		board[x][y] = i;
		used[x][y] = 1;
		if (dfs(idx+1))	return 1;
		used[x][y] = 0;
		COL[x].erase(i), ROW[y].erase(i);
	}
	return 0;
}
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		order.clear();
		for (int i = 0; i < m; i++) {
			char s[8];
			int x, c, l;
			scanf("%d %s %d", &goal[i], s, &c);
			EXP[i] = s[0], var[i].clear();
			for (int j = 0; j < c; j++) {
				scanf("%d", &l);
				order.push_back({(l-1)/n, (l-1)%n});
				var[i].push_back(l);
			}
		}
		for (int i = 0; i < n; i++)
			ROW[i].clear(), COL[i].clear();
		memset(used, 0, sizeof(used));
		dfs(0);
	}
	return 0;
}

