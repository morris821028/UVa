#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector> 
#include <queue>
#include <algorithm>
using namespace std;

vector<int> g[26];
char path[32];
int n, m, st, ed, used[26];
int bused[26] = {}, tused = 0;
int bfs(int u, int comp) {
	tused++;
	int cnt = 0, v;
	queue<int> Q;
	Q.push(u), bused[u] = tused;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		cnt++;
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			if (bused[v] != tused && used[v] == 0) {
				bused[v] = tused;
				Q.push(v);
			}
		}
	}
	return cnt == comp;
}
int dfs(int idx, int u) {
	path[idx] = u + 'A';
	if (idx < n - 1 && used[ed])	return 0;
	if (idx == n-1) {
		path[n] = '\0';
		puts(path);
		return 1;
	}
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (used[v] || !bfs(v, n - idx - 1))	
			continue;
		used[v] = 1;
		if(dfs(idx+1, v))	return 1;
		used[v] = 0;
	}
	return 0;
}
int main() {
	int testcase, cases = 0;
	int x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		char name[26][4], s1[4], s2[4], buf[26];
		int mg[26][26] = {};
		for (int i = 0; i < 26; i++)
			g[i].clear();
		for (int i = 0; i < n; i++)
			scanf("%s", name[i]);
		for (int i = 0; i < m; i++) {
			scanf("%s %s", s1, s2);
			x = s1[0] - 'A', y = s2[0] - 'A';
			mg[x][y] = mg[y][x] = 1;
		}
		st = name[0][0] - 'A', ed = name[n-1][0] - 'A';
		for (int i = 0; i < 26; i++) {
			for (int j = 0; j < 26; j++) {
				if (mg[i][j])
					g[i].push_back(j);
			}
		}
		printf("Case %d: ", ++cases);
		memset(used, 0, sizeof(used));
		used[st] = 1;
		int f = dfs(0, st);
		if (!f)	puts("impossible");
	}
	return 0;
}
/*
3
12 14
A B C D E F U V W X Y Z
A F
A V
B U
B W
C D
C V
D Y
D W
E X
E Z
F U
F Y
U Z
W X
3 2
A B C
A B
A C

50
4 5
L N I K
L N
I L
I N
K N
K I
*/
