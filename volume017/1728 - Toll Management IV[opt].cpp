#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 10005;
const int MAXM = 100005;
struct EdgeIn {
	int x, y, w;
	EdgeIn() {}
	EdgeIn(int x, int y, int w):
		x(x), y(y), w(w) {}
} edges[MAXM];

struct Edge {
	int to, i;
	Edge() {}
	Edge(int to, int i):
		to(to), i(i) {}
	bool operator<(const Edge &e) const {
		return to < e.to;
	}
};

vector<Edge> g[MAXN];

int16_t depth[MAXN], visited[MAXN];
int16_t st_p[MAXN][16], st_w[MAXN][16];
int16_t tree[MAXN][16];
int16_t parent[MAXN];
void dfs(int u, int p, int dep) {
	depth[u] = dep;
	
	for (int i = 1, j = 2; j <= dep; i++, j <<= 1) {
		st_p[u][i] = st_p[st_p[u][i-1]][i-1];
		st_w[u][i] = max(st_w[u][i-1], st_w[st_p[u][i-1]][i-1]);
	}
	
	for (auto e : g[u]) {
		if (e.to == p)
			continue;
		st_p[e.to][0] = u;
		st_w[e.to][0] = edges[e.i].w;
		dfs(e.to, u, dep+1);
	}
}

void build(int n) {
	memset(st_p, -1, sizeof(st_p));
	dfs(1, -1, 0);
}


static inline int log2int(int32_t x) {
	return 32 - __builtin_clz(x); 
}

int path(int x, int y, int16_t c) {
	if (x == y)
		return 0;
	if (depth[x] < depth[y])
		swap(x, y);
	int16_t ret = SHRT_MIN;
	if (depth[x] > depth[y]) {
		int diff = depth[x] - depth[y];
		for (int i = 0; diff; i++) {
			if ((diff>>i)&1) {
				ret = max(ret, st_w[x][i]);
				tree[x][i] = min(tree[x][i], c);
				x = st_p[x][i];
				diff ^= 1<<i;
			}
		}
	}
	
	if (x != y) {
		int h = log2int(depth[x])+1;
		for (int i = h; i >= 0; i--) {
			if (st_p[x][i] != st_p[y][i]) {
				ret = max(ret, st_w[x][i]);
				ret = max(ret, st_w[y][i]);
				tree[x][i] = min(tree[x][i], c);
				tree[y][i] = min(tree[y][i], c);
				x = st_p[x][i];
				y = st_p[y][i];
			}
		}
		ret = max(ret, st_w[x][0]);
		ret = max(ret, st_w[y][0]);
		tree[x][0] = min(tree[x][0], c);
		tree[y][0] = min(tree[y][0], c);
	}
	
	return ret;
}

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

int main() {
	int testcase, cases = 0;
	int n, m;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d", &n, &m);
		ReadInt(&n), ReadInt(&m);

		for (int i = 0; i <= n; i++)
			g[i].clear();
		for (int i = 1; i <= m; i++) {
			int x, y, w;
//			scanf("%d %d %d", &x, &y, &w);
			ReadInt(&x), ReadInt(&y), ReadInt(&w);
			edges[i] = EdgeIn(x, y, w);
			if (i < n) {
				g[x].push_back(Edge(y, i));
				g[y].push_back(Edge(x, i));
			}
		}

		for (int i = 0; i <= n; i++)
			sort(g[i].begin(), g[i].end());
		
		build(n);
		
		int64_t ret = 0;
		memset(tree, 0x3f, sizeof(tree));
		
		// for non-tree edge
		for (int i = n; i <= m; i++) {
			int64_t j = i;
			const int a = -1;
			const int b = edges[i].w - path(edges[i].x, edges[i].y, edges[i].w);
			ret += j * a + j*j * b;
		}
		
		// for tree edge
		for (int i = log2int(n)+1; i >= 0; i--) {
			for (int j = 1; j <= n; j++) {
				if ((1<<i) > depth[j])
					continue;
				tree[j][i-1] = min(tree[j][i-1], tree[j][i]);
				tree[st_p[j][i-1]][i-1] = min(tree[st_p[j][i-1]][i-1], tree[j][i]);
			}
		}
		for (int i = 1; i < n; i++) {
			int x = edges[i].x, y = edges[i].y, w = edges[i].w;
			if (st_p[y][0] == x)
				swap(x, y);
			int64_t j = i;
			const int a = tree[x][0] == 0x3f3f ? -1 : (tree[x][0] - w);
			const int b = -1;
			ret += j * a + j*j * b;
		}
		
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
2
3  3
1  2  5
2  3  7
1  3  10
4  5
1  3  1
3  4  2
1  2  3
1  4  4
2  4  5
*/
