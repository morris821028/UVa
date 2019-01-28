#include <bits/stdc++.h>
using namespace std;

const int MAXN = 65536;
set<int> G[MAXN];
int W[MAXN];
int used[MAXN], cases = 0;
int parent[MAXN];
int same_tree(int u, int v) {
	while (parent[u] != -1)
		u = parent[u];
	while (parent[v] != -1)
		v = parent[v];
	return u == v;
}

int main() {
	srand(time(NULL));
	int testcase = 1;
//	printf("%d\n", testcase);
    while (testcase--) {
    	int w, h, n, m, q;
    	n = 30000, m = 100000;
    	printf("%d %d\n", n, m);
    	for (int i = 1; i <= n; i++) {
    		int w = rand()%2;
    		printf("%d%c", w, " \n"[i==n-1]);
    		W[i] = w, G[i].clear();
    		parent[i] = -1;
    	}

		int e = 0;
		vector<pair<int, int>> E;
		for (int i = 0; i < m; i++) {
			int cmd;
			if (e != n-1) {
				cmd = rand()%4+1;
				if (i < n)
					cmd = 1;
			} else {
				cmd = rand()%3+2;
			}
			if (e == 0 && cmd == 2)
				cmd = 4;
			if (cmd == 2 && rand()%100 > 1)
				cmd = rand()%2+3;
			if (cmd == 1) {
				int x, y = rand()%n+1;
				do {
					x = rand()%n+1;
					if (parent[x] != -1)
						continue;
					break;
				} while (true);
				if (i < n)
					x = i+2, y = i+1;
				do {
					if (!same_tree(x, y))
						break;
					y = rand()%n+1;
				} while (true);
				printf("%d %d %d\n", cmd, x, y);
				e++;
				parent[x] = y;
				E.push_back({x, y});
			} else if (cmd == 2) {
				int d = rand()%E.size();
				if (rand()%100 > 10) {
					for (int i = 0; i < E.size(); i++) {
						if (E[d].first != E[d].second+1) {
							d = i;
							break;
						}
					}
				}
				int x = E[d].first, y = E[d].second;
				E.erase(E.begin()+d, E.begin()+d+1);
				parent[x] = -1;
				e--;
				printf("%d %d\n", cmd, x);
			} else if (cmd == 3) {
				printf("%d %d %d\n", cmd, rand()%n+1, rand()%10);
			} else {
				printf("%d %d\n", cmd, rand()%n+1);
			}
		}
    }
	return 0;
}

