#include <stdio.h> 
#include <vector>
#include <queue>
using namespace std;
void addPath(int u, int v, int k, int n, vector<int> g[], int weight[]) {
	static int used[32767] = {}, testcase = 0;
	static int pre[32767];
	testcase++;
	queue<int> Q;
	int x, y;
	Q.push(u), used[u] = testcase;
	while (!Q.empty()) {
		x = Q.front(), Q.pop();
		for (int i = 0; i < g[x].size(); i++) {
			y = g[x][i];
			if (used[y] != testcase) {
				used[y] = testcase;
				pre[y] = x, Q.push(y);
			}
		}
		if (used[v] == testcase)	break;
	}
	for (int i = v; i != u; i = pre[i])
		weight[i] += k;
	weight[u] += k;
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out.txt", "w+t", stdout); 
	int n, m, x, y, u, v, k;
	while (scanf("%d %d", &n, &m) == 2) {
		vector<int> g[32767];
		int weight[32767] = {};
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			g[x].push_back(y);
			g[y].push_back(x);
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &u, &v, &k);
			addPath(u, v, k, n, g, weight);
		}
		for (int i = 0; i < n; i++)
			printf("%d%s", weight[i], i == n-1 ? "" : " ");
		puts("");
	}
	return 0;
}
/*
7 4
0 1
0 2
1 3
1 4
2 5
2 6
2 3 1
3 4 2
0 5 4
6 6 8
*/
