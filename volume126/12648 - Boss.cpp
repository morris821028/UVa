#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;

int visited[512];
int age[512];
vector<int> g[512], boss[512];
void dfs(int u, int em) {
	visited[u] = 1, boss[em].push_back(u);
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if(visited[v])	continue;
		dfs(v, em);
	}
}
int main() {
	int N, M, I, x, y, em;
	char cmd[10];
	while(scanf("%d %d %d", &N, &M, &I) == 3) {
		for(int i = 1; i <= N; i++) {
			scanf("%d", &age[i]);
			g[i].clear(), boss[i].clear();
		}
		for(int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			g[y].push_back(x);
		}
		
		int mp[512];
		for(int i = 1; i <= N; i++) {
			mp[i] = i;
			memset(visited, 0, sizeof(visited));
			visited[i] = 1;
			for(int j = 0; j < g[i].size(); j++)
				if(!visited[g[i][j]])
					dfs(g[i][j], i);
		}
		
		for(int i = 0; i < I; i++) {
			scanf("%s", cmd);
			if(cmd[0] == 'P') {
				scanf("%d", &em);
				int ret = 0x3f3f3f3f;
				em = mp[em];
				for(int i = 0; i < boss[em].size(); i++)
					ret = min(ret, age[boss[em][i]]);
				if(ret == 0x3f3f3f3f)
					puts("*");
				else
					printf("%d\n", ret);
			} else {
				scanf("%d %d", &x, &y);
				swap(age[mp[x]], age[mp[y]]);
				swap(mp[x], mp[y]);
			}
		}
	}
	return 0;
} 
/*
7 8 9
21 33 33 18 42 22 26
1 2
1 3
2 5
3 5
3 6
4 6
4 7
6 7
P 7
T 4 2
P 7
P 5
T 1 4
P 7
T 4 7
P 2
P 6
6 5 6
10 20 30 40 50 60
1 5
1 4
3 6
2 5
4 5
P 1
P 5
P 6
T 1 6
P 1
P 4
*/
