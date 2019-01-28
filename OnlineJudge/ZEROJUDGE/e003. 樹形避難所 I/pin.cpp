#include <bits/stdc++.h>
using namespace std;

const int MAXN = 65536;
set<int> G[MAXN];
int W[MAXN];
int used[MAXN], cases = 0;

int same_tree(int u, int v) {
	queue<int> Q;
	int sum = 0;
	cases++, used[u] = cases;
	Q.push(u);
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		if (u == v)
			return 1;
		for (auto v : G[u]) {
			if (used[v] != cases) {
				used[v]	 = cases;
				Q.push(v);
			}
		}
	}
	return 0;
}

int main() {
	srand(time(NULL));
	int testcase = 1;
//	printf("%d\n", testcase);
    while (testcase--) {
    	int w, h, n, m, q;
    	n = 10, m = 1000;
    	printf("%d %d\n", n, m);
    	for (int i = 1; i <= n; i++) {
    		int w = rand()%2;
    		printf("%d%c", w, " \n"[i==n-1]);
    		W[i] = w, G[i].clear();
    	}

		int e = 0;
		vector<pair<int, int>> E;
		for (int i = 0; i < m; i++) {
			int cmd;
			if (e != n-1)
				cmd = rand()%4+1;
			else
				cmd = rand()%3+2;
			if (e == 0 && cmd == 2)
				cmd = 4;
			if (cmd == 2 && rand()%100 > 10)
				cmd = rand()%2+3;
			if (cmd == 1) {
				int x, y;
				do {
					x = rand()%n+1, y = rand()%n+1;
					if (!same_tree(x, y))
						break;
				} while (true);
				printf("%d %d %d\n", cmd, x, y);
				e++;
				G[x].insert(y);
				G[y].insert(x);
				E.push_back({x, y});
			} else if (cmd == 2) {
				int d = rand()%E.size();
				int x = E[d].first, y = E[d].second;
				E.erase(E.begin()+d, E.begin()+d+1);
				G[x].erase(y);
				G[y].erase(x);
				e--;
				printf("%d %d %d\n", cmd, x, y);
			} else if (cmd == 3) {
				printf("%d %d %d\n", cmd, rand()%n+1, rand()%33);
			} else {
				printf("%d %d\n", cmd, rand()%n+1);
			}
		}
    }
	return 0;
}

