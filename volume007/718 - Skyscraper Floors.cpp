#include <bits/stdc++.h>
using namespace std;
const int MAXN = 128;
vector<int> g[MAXN];
int F, E, A, B;

// a x + by = g
void exgcd(int x, int y, int &g, int &a, int &b) {
    if (y == 0)
        g = x, a = 1, b = 0;
    else
        exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}

int create_edge(int x, int y, int t) {
	if (t >= y && (t-y)%x == 0)
		return 1;
	return 0;
}
int create_edge2(int x1, int y1, int x2, int y2) {
	int x = x1, y = -x2, z = y2 - y1;	// y1 + a x1 = y2 + b x2
	int g, a, b;
	exgcd(x, y, g, a, b);
	if (z%g)
		return 0;
	int lower, upper;
	double mx;
	// ax + by = g
	// a = a + y / g * k
	// b = b - x / g * k

	mx = (double) (F - y1) / x1; // a x1 + y1 <= F
	// z/g*a + y/g*k <= mx
	// z/g*a + y/g*k >= 0
	if (y / g > 0) {
		lower = (int) ceil((double) -a*z/y);
		upper = (int) floor((mx*g - a*z)/y);
	} else {
		upper = (int) floor((double) -a*z/y);
		lower = (int) ceil((mx*g - a*z)/y);
	}
	mx = (double) (F - y2) / x2;
	if (x / g > 0) {
		upper = min(upper, (int) floor((double) b*z/x));
		lower = max(lower, (int) ceil((b*z - mx*g)/x));
	} else {
		upper = min(upper, (int) floor((b*z - mx*g)/x));
		lower = max(lower, (int) ceil((double) b*z/x));
	}
	return lower <= upper;
}
void add_edge(int u, int v) {
	g[u].push_back(v);
	g[v].push_back(u);
}
int bfs(int st, int ed) {
	int used[MAXN] = {};
	queue<int> Q;
	Q.push(st), used[st] = 1;
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		if (u == ed)
			return 1;
		for (auto v: g[u]) {
			if (!used[v]) {
				used[v] = 1, Q.push(v);
			}
		}
	}
	return 0;
}
int main() {
	int testcase;
	int x[MAXN], y[MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d %d", &F, &E, &A, &B);
		for (int i = 0; i < E+2; i++)
			g[i].clear();
		for (int i = 0; i < E; i++) {
			scanf("%d %d", &x[i], &y[i]);
			if (create_edge(x[i], y[i], A))
				add_edge(i, E);
			if (create_edge(x[i], y[i], B))
				add_edge(i, E+1);
		}
		for (int i = 0; i < E; i++) {
			for (int j = i+1; j < E; j++) {
				if (create_edge2(x[i], y[i], x[j], y[j]))
					add_edge(i, j);
			}
		}
		int ret = bfs(E, E+1);
		if (ret)
			puts("It is possible to move the furniture.");
		else
			puts("The furniture cannot be moved.");
	}
	return 0;
}
/*
2
22 4 0 6
3 2
4 7
13 6
10 0
1000 2 500 777
2 0
2 1
*/
