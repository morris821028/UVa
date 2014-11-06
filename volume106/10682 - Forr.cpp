#include <stdio.h>
#include <string.h> 
#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

map<string, int> R;
string name[512];
int rename(char s[]) {
	int &x = R[s];
	if (x == 0)	x = R.size(), name[x] = s;
	return x;
}
vector< pair<int, int> > g[512];
int ag[512][512];
int dist[512][512];
pair<int, int> from[512][512];
void bfs(int st, int ed) {
	queue<int> Q, P;
	int u, p, v;
	memset(dist, 0, sizeof(dist));
	Q.push(st), P.push(0);
	ag[st][0] = 0x3f3f3f3f, dist[st][0] = 1;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		p = P.front(), P.pop();
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i].first;
			if (ag[u][v] <= ag[u][p]) {
				if (dist[v][u] == 0) {
					dist[v][u] = dist[u][p] + 1;
					from[v][u] = make_pair(u, p);
					Q.push(v), P.push(u);
				}
			}
		}
	}
	int ret = 0x3f3f3f3f;
	for (int i = 1; i <= R.size(); i++) {
		if (dist[ed][i])
			ret = min(ret, dist[ed][i]);
	}
	if (ret == 0x3f3f3f3f) {
		puts("No valid route.");
		return ;
	}
	for (int i = 1; i <= R.size(); i++) {
		if (dist[ed][i] == ret) {
			pair<int, int> state = make_pair(ed, i);
			while (state != make_pair(st, 0)) {
				printf("%s ", name[state.first].c_str());
				state = from[state.first][state.second];
			}
			printf("%s\n", name[state.first].c_str());
			break;
		}
	}
}
int main() {
	int n, w;
	int x, y, cases = 0;
	char s1[1024], s2[1024];
	while (scanf("%d", &n) == 1) {
		if (cases++)	puts("");
		R.clear();
		for (int i = 0; i < n; i++) {
			scanf("%s %s %d", s1, s2, &w);
			x = rename(s1), y = rename(s2);
			g[x].push_back(make_pair(y, w));
			g[y].push_back(make_pair(x, w));
			ag[x][y] = ag[y][x] = w;
//			printf("%d %d\n", x, y);
		}
		for (int i = 1; i <= R.size(); i++)
			sort(g[i].begin(), g[i].end());
		scanf("%s %s", s1, s2);
		x = rename(s1), y = rename(s2);
		bfs(y, x);
		for (int i = 0; i <= R.size(); i++)
			g[i].clear();
	}
	return 0;
}
/*
5
Natal Assu 50
Mossoro PaudosFerros 80
Assu Mossoro 40
Marcelino PaudosFerros 100
Assu PaudosFerros 65
Natal Mossoro

2
Limoeiro MoradaNova 140
Limoeiro Jaguaribe 130
Jaguaribe MoradaNova

4
Mossoro Paris 233
Mossoro NewYork 412
NewYork Tokio 501
Tokio Paris 420
Mossoro Tokio

4
A B 12
A C 15
C D 20
B D 20
A D
*/
