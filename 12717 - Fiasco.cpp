#include <stdio.h> 
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

vector<int> g[2505];
int used[25005];
int in_x[25005], in_y[25005], in_w[25005];
map< pair<int, int>, int> shortest_tree;

void bfs(int source) {
	queue<int> 	Q;
	int 		u, v, e = 0;
	Q.push(source), used[source] = 1;
	while(!Q.empty()) {
		u = Q.front(), Q.pop();
		for(int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			if(used[v])	continue;
			used[v] = 1;
			shortest_tree[make_pair(u, v)] = in_w[e], e++;
			Q.push(v);
		}
	}
}
int main() {
	int testcase, cases = 0;
	int n, m, source;
	int x, y, w;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d %d", &n, &m, &source);
		
		for(int i = 1; i <= n; i++) {
			g[i].clear();
			used[i] = 0;
		}
		shortest_tree.clear();
		
		for(int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			g[x].push_back(y);
			g[y].push_back(x);
			in_x[i] = x, in_y[i] = y, in_w[i] = w;
		}
		
		for(int i = 1; i <= n; i++)
			sort(g[i].begin(), g[i].end());
		sort(in_w, in_w + m);
		bfs(source);
		
		printf("Case %d:\n", ++cases);
		map< pair<int, int>, int>::iterator it, jt, kt;
		int e = m - 1;
		kt = shortest_tree.end();
		for(int i = 0; i < m; i++) {
			it = shortest_tree.find(make_pair(in_x[i], in_y[i]));
			jt = shortest_tree.find(make_pair(in_y[i], in_x[i]));
			if(it != kt)
				w = it->second;
			else if(jt != kt)
				w = jt->second;
			else
				w = in_w[e], e--;
			printf("%d %d %d\n", in_x[i], in_y[i], w);
		}
	}
	return 0;
}
/*
1
7 9 5
2 4 2
1 4 8
7 2 6
3 4 7
5 7 5
7 3 9
6 1 1
6 3 4
5 6 3
*/
