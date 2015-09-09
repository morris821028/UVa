#include <bits/stdc++.h>
using namespace std;
template<typename WTYPE, int MAXN, bool FUNC(WTYPE, WTYPE)> 
class MST {
public:
	struct Edge {
    	int x, y;
		WTYPE v;
    	Edge(int a=0, int b=0, WTYPE c=0):
        	x(a), y(b), v(c) {}
    	bool operator<(const Edge &a) const {
    		return FUNC(v, a.v);
    	}
	};
	vector<Edge> e, mst;
	int N, p[MAXN], rank[MAXN];
	WTYPE cost; 
	void init(int n) {
		N = n;
		for(int i = 0; i <= N; i++)
	        p[i] = i, rank[i] = 1;
	    e.clear(), mst.clear();
	}
	void addedge(int x, int y, WTYPE w) {
		e.push_back(Edge(x, y, w));
	}
	int kruscal() {
		sort(e.begin(), e.end());
		cost = 0;
	    for(int i = 0; i < e.size(); i++) {
	        if(joint(e[i].x, e[i].y))
	        	mst.push_back(e[i]), cost += e[i].v;
	    }
	    return mst.size() == N-1;
	}
	int findp(int x) {
	    return p[x] == x ? x : (p[x] = findp(p[x]));
	}
	int joint(int x, int y) {
	    x = findp(x), y = findp(y);
	    if(x == y)
	        return 0;
	    if(rank[x] > rank[y])
	        rank[x] += rank[y], p[y] = x;
	    else
	        rank[y] += rank[x], p[x] = y;
	    return 1;
	}
};
bool cmp(int a, int b) { return a > b; }
MST<int, 32767, cmp> mst;

const int MAXN = 32767;
const int MAXLOGN = 17;
int fa[MAXLOGN][MAXN], visited[MAXN], dep[MAXN];
int fw[MAXLOGN][MAXN];
vector< pair<int, int> > g[MAXN];
void dfs(int u) {
    visited[u] = 1;
    for (auto e : g[u]) {
    	int v = e.first, w = e.second;
    	if (visited[v])	continue;
        fa[0][v] = u, fw[0][v] = w;
        dep[v] = dep[u] + 1;
        dfs(v);
    }
}
int path(int x, int y) {
	if (dep[x] < dep[y])	swap(x, y);
    int d = dep[x] - dep[y];
    int ret = INT_MAX;
    for (int i = MAXLOGN-1; i >= 0; i--) {
        if ((d>>i)&1) {
            d -= 1<<i;
            ret = min(ret, fw[i][x]);
            x = fa[i][x];
        }
    }
    if (x == y)	return ret;
    for (int i = MAXLOGN-1; i >= 0; i--) {
        if (fa[i][x] != fa[i][y]) {
        	ret = min(ret, fw[i][x]);
        	ret = min(ret, fw[i][y]);
            x = fa[i][x], y = fa[i][y];
        }
    }
    ret = min(ret, fw[0][x]);
    ret = min(ret, fw[0][y]);
    return ret;
}
int main() {
	int n, m, q;
	int x, y, w;
	while (scanf("%d %d", &n, &m) == 2) {
		mst.init(n);	// vertex [0, n-1]
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			x--, y--;
			mst.addedge(x, y, w);
		}
		mst.kruscal();
		
		for (int i = 0; i < n; i++)
			g[i].clear(), visited[i] = 0;
		for (auto e : mst.mst) {
			g[e.x].push_back({e.y, e.v});
			g[e.y].push_back({e.x, e.v});
		}
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0)
				dep[i] = 0, dfs(i);
		}
		for (int i = 1; i < MAXLOGN; i++) {
            for (int j = 0; j < n; j++) {
                fa[i][j] = fa[i-1][fa[i-1][j]];
                fw[i][j] = min(fw[i-1][fa[i-1][j]], fw[i-1][j]);
            }
        }
                
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &x, &y);
			x-- , y--; 
			if (mst.findp(x) != mst.findp(y))
				printf("-1\n");
			else
				printf("%d\n", path(x, y));
		}
	}
	return 0;
}

