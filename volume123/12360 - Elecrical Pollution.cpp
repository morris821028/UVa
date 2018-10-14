#include <bits/stdc++.h>
using namespace std;

inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if(p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while((c = readchar()) < '-')    {if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while((c = readchar()) >= '0')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}

const int MAXN = 30005;
struct Measure {
	int x, y, a;
	Measure() {}
	Measure(int x, int y, int a):
		x(x), y(y), a(a) {}
} D[MAXN];
struct Edge {
	int to, w;
	Edge() {}
	Edge(int to, int w):
		to(to), w(w) {}
};;
vector<Edge> g[MAXN];
int val[MAXN], solved[MAXN];
int visited[MAXN][2], visited2[MAXN], belong[MAXN];
int path[MAXN][2];
queue<int> Q;

void dfs(int u, int alter, int sum, int root) {
	if (visited[u][alter])
		return ;
	visited[u][alter] = 1;
	path[u][alter] = sum;

	// find the odd cycle
	if (visited[u][alter^1] && !solved[root]) {
		val[root] = (path[u][alter^1] + sum)>>1, solved[root] = 1;
		Q.push(root);
	}

	for (auto e: g[u])
		dfs(e.to, alter^1, sum + (alter ? -e.w : e.w), root);
}

void dfs2(int u, int alter, int root) {
	if (visited2[u])
		return ;
	visited2[u] = alter, belong[u] = root;
	for (auto e: g[u]) {
		val[e.to] = e.w - val[u];
		dfs2(e.to, -alter, root);
	}
}

int main() {
	int n, m;
//	while (scanf("%d %d", &n, &m) == 2 && n) {
	while (ReadInt(&n), ReadInt(&m), n) {
		vector<int> X;
		for (int i = 0; i < n; i++) {
			int x, y, a;
//			scanf("%d %d %d", &x, &y, &a);
			ReadInt(&x), ReadInt(&y), ReadInt(&a);
			D[i] = Measure(x, y, a);
			X.emplace_back(x);
			X.emplace_back(y);
		}

		sort(X.begin(), X.end());
		X.resize(unique(X.begin(), X.end()) - X.begin());

		for (int i = 0; i < X.size(); i++) {
			g[i].clear();
			val[i] = 0, solved[i] = 0;
			visited[i][0] = visited[i][1] = 0;
			visited2[i] = 0;
			belong[i] = -1;
		}

		while (!Q.empty())
			Q.pop();
		for (int i = 0; i < n; i++) {
			int x = lower_bound(X.begin(), X.end(), D[i].x) - X.begin();
			int y = lower_bound(X.begin(), X.end(), D[i].y) - X.begin();
			if (x == y) {
				val[x] = D[i].a, solved[x] = 1;
				Q.push(x);
			} else {
				g[x].push_back(Edge(y, D[i].a));
				g[y].push_back(Edge(x, D[i].a));
			}
		}
		
		for (int i = 0; i < X.size(); i++) {
			if (!solved[i] && !visited[i][0] && !visited[i][1])
				dfs(i, 0, 0, i);
		}
		
		// solved the component which exists odd cycle
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			for (auto e: g[u]) {
				if (solved[e.to])
					continue;
				val[e.to] = e.w - val[u];
				solved[e.to] = 1;
				Q.push(e.to);
			}
		}

		// graph which does not contain any odd cycle
		for (int i = 0; i < X.size(); i++) {
			if (!solved[i] && !visited2[i])
				dfs2(i, 1, i);
		}
		
		for (int i = 0; i < m; i++) {
			int x, y, a, b;
//			scanf("%d %d", &x, &y);
			ReadInt(&x), ReadInt(&y);
			a = lower_bound(X.begin(), X.end(), x) - X.begin();
			b = lower_bound(X.begin(), X.end(), y) - X.begin();
			if (a >= X.size() || X[a] != x || b >= X.size() || X[b] != y) {
				puts("*");
				continue;
			}
			x = a, y = b;
			if (x == y) {
				if (solved[x])
					printf("%d\n", val[x]);
				else
					puts("*");
			} else if (solved[x] && solved[y]) {
				printf("%d\n", val[x] + val[y]);
			} else if (belong[x] == belong[y] && visited2[x]+visited2[y] == 0) {
				printf("%d\n", val[x] + val[y]);
			} else {
				puts("*");
			}
		}
		puts("-");
	}
	return 0;
}
/*
3 3
30 -10 3
30 20 15
40 20 2
-10 40
40 -10
-10 -10

6 8
0 1 11
0 3 8
1 0 11
3 0 8
4 4 0
3 5 6
1 5
0 3
3 0
4 3
0 2
2 4
4 4
5 5

0 0
*/
