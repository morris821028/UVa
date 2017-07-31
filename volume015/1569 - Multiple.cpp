#include <bits/stdc++.h>
using namespace std;

void bfs(int n, int m, int d[]) {
	if (n == 0) {
		puts("0");
		return ;
	}
	sort(d, d+m);
	const int MAXN = 8192;
	int used[MAXN] = {};
	pair<int, int> from[MAXN];
	queue<int> Q;
	used[0] = 1;
	Q.push(0);
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		for (int i = 0; i < m; i++) {
			if (v == 0 && d[i] == 0)
				continue;
			int t = (v*10 + d[i])%n;
			if (t == 0) {
				vector<int> ret;
				ret.push_back(d[i]);
				while (v) {
					ret.push_back(from[v].second);
					v = from[v].first;
				}
				for (int i = ret.size()-1; i >= 0; i--)
					printf("%d", ret[i]);
				puts("");
				return ;
			}
			if (used[t])
				continue;
			used[t] = 1, from[t] = make_pair(v, d[i]);
			Q.push(t);
		}
	}
	puts("0");
}
int main() {
	int n, m, d[32];
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < m; i++)
			scanf("%d", &d[i]);
		bfs(n, m, d);
	}
	return 0;
}
/*
0
3
1
2
3
51
3
1
7
9
*/
