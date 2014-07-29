#include <stdio.h>
#include <vector>
#include <algorithm>
#include <queue>
#include <string.h>
using namespace std;

vector<int> g[1024];
int main() {
	int n, m, x, y;
	while(scanf("%d %d", &n, &m) == 2 && n + m) {
		for(int i = 0; i < n; i++)
			g[i].clear();
		for(int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		int used[1024] = {};
		for(int i = n - 1; i >= 0; i--) {
			if(used[i])	continue;
			for(int j = 0; j < g[i].size(); j++)
				used[g[i][j]] = 1;
		}
		for(int i = 0; i < n; i++)
			printf("%d", used[i]);
		puts("");
	}
	return 0;
}
