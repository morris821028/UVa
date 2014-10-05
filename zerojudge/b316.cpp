#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> g[1024];
int main() {
	int N, M, K;
	int x, y;
	while (scanf("%d %d %d", &N, &M, &K) == 3) {
		for (int i = 0; i < N; i++)
			g[i].clear();
		for (int i = 0; i < M; i++) {
			scanf("%d %d", &x, &y);
			if (x > y)	swap(x, y);
			g[x].push_back(y);
		}
		for (int i = 0; i < N; i++)
			sort(g[i].begin(), g[i].end());
		int pass[1024] = {};
		int now = 0, x, sum = 0;
		pass[0] = --K;
		for (int i = 0; i < N; i++) {
			if (g[i].size() == 0)	continue;
			int u = i, v, div = pass[u] % g[i].size();
			for (int j = 0; j < g[i].size(); j++) {
				v = g[i][j];
				pass[v] += pass[u] / g[i].size();
				if (j < div)
					pass[v]++;
			} 
		}
		for (; g[now].size(); ) {
			x = pass[now]%g[now].size();
			now = g[now][x];
//			printf("-> %d\n", now);
		}
		printf("%d\n", now);
	}
	return 0;
}
/*
5 6 1
0 1
0 2
1 2
2 3
0 4
1 4

5 6 2
0 1
0 2
1 2
2 3
0 4
1 4

5 6 3
0 1
0 2
1 2
2 3
0 4
1 4

5 6 4
0 1
0 2
1 2
2 3
0 4
1 4

*/

