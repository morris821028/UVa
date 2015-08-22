#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 65536;

int A[MAXN];
int dep[MAXN];
int parent[MAXN], weight[MAXN];
vector<int> g[MAXN];
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)	return 0;
	if (weight[x] > weight[y])
		weight[x] += weight[y], parent[y] = x;
	else
		weight[y] += weight[x], parent[x] = y;
	return 1;
}
void merge(int X, int Y) {
	if (joint(X, Y))
		g[X].push_back(Y), g[Y].push_back(X);
}
int route[MAXN];
int dfs(int idx, int u, int p, int Y, int K, int &ret) {
	if (u == Y) {
		for (int i = 0; i < idx; i++)
			ret += A[route[i]] <= K;
		return 1;
	}
	for (auto v : g[u]) {
		if (v == p)	continue;
		route[idx] = v;
		if (dfs(idx+1, v, u, Y, K, ret))
			return 1;
	}
	return 0;
}
int path(int X, int Y, int K) {
	if (findp(X) != findp(Y))	return 0;
	int ret = 0;
	route[0] = X;
	dfs(1, X, 0, Y, K, ret);
	return ret;
}
int main() {
	int N, Q, cmd;
	int X, Y, K;
	while (scanf("%d %d", &N, &Q) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
			
		for (int i = 1; i <= N; i++)
			parent[i] = i, g[i].clear(), dep[i] = 0;
		
		int d = 0;
		
		for (int i = 0; i < Q; i++) {
			scanf("%d %d %d", &cmd, &X, &Y);
			X ^= d, Y ^= d;
			if (cmd == 0) {
				merge(X, Y);
			} else {
				scanf("%d", &K);
				K ^= d;
				d = path(X, Y, K);
				printf("%d\n", d);
			}
		}
		
	}
	return 0;
}
/*
7 11
1 5 2 6 3 7 4
0 2 4
0 1 2
0 1 3
0 3 7
1 4 7 3
1 5 6 7
0 2 5
0 5 3
1 4 5 5
0 3 6
1 5 6 4
*/
