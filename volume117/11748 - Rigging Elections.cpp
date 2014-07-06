#include <stdio.h> 
#include <vector>
#include <string.h>
using namespace std;

vector<int> g[105];
int used[105];
void dfs(int u) {
	used[u] = 1;
	for(int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if(used[v] == 0)
			dfs(v);
	}
}
int main() {
	int n, m, c, x;
	int rank[105][105];
	while(scanf("%d %d %d", &n, &m, &c) == 3 && n+m+c) {
		for(int i = 1; i <= n; i++) 
			g[i].clear();
			
		for(int i = 0; i < m; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%d", &x);
				rank[i][x] = j;
			}
		}
		
		for(int i = 1; i <= n; i++) {
			for(int j = i + 1; j <= n; j++) {
				int A = 0, B = 0;
				for(int k = 0; k < m; k++) {
					if(rank[k][i] < rank[k][j])
						A++;
					else
						B++;
				}
				if(A > B)
					g[i].push_back(j);
				else
					g[j].push_back(i);
			}
		}
		
		memset(used, 0, sizeof(used));
		dfs(c);
		int win = 0;
		for(int i = 1; i <= n; i++)
			win += used[i];
		puts(win == n ? "yes" : "no");
	}
	return 0;
}
