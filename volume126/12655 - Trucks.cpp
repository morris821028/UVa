#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
#include <math.h>
#include <vector>
using namespace std;
struct E {
    int x, y, v;
    E(int a=0, int b=0, int c=0):
    x(a), y(b), v(c) {}
    bool operator<(const E &a) const {
        return  v > a.v;
    }
};
E D[100005];
int visited[32767];
vector<E> tree[32767];
int parent[32767], weight[32767];
int findp(int x) {
    return parent[x] == x ? x : (parent[x] = findp(parent[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if(x == y)
        return 0;
    if(weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}
int kruscal(int n, int m) {
	struct E {
int x, y, v;
E(int a=0, int b=0, int c=0):
x(a), y(b), v(c) {}
bool operator<(const E &a) const {
return v > a.v;
}
};
    int sum = 0;
    
    sort(D, D+m);
    for(int i = 0; i <= n; i++) {
        parent[i] = i, weight[i] = 1;
        tree[i].clear();
    }
    
    for(int i = 0; i < m; i++) {
        if(joint(D[i].x, D[i].y)) {
        	sum += D[i].v;
        	tree[D[i].x].push_back(E(D[i].x, D[i].y, D[i].v));
        	tree[D[i].y].push_back(E(D[i].y, D[i].x, D[i].v));
        }
    }
    return sum;
}
int dp[32767][20], dpw[32767][20];
int treeLevel[32767], treePath[32767];
void dfs(int u, int p, int level) {
	treeLevel[u] = level, treePath[level] = u;
	for(int i = 1; (1<<i) < level; i++) {
		dp[u][i] = min(dp[u][i-1], dp[dpw[u][i-1]][i-1]);
		dpw[u][i] = treePath[level-(1<<i)];
	}
	for(int i = 0; i < tree[u].size(); i++) {
		int v = tree[u][i].y;
		if(v == p)	continue;
		dp[v][0] = tree[u][i].v;
		dpw[v][0] = u;
		dfs(v, u, level + 1);
	}
}

// LCA
vector< pair<int, int> > Q[32767];// query pair, input index - node
int LCA[131072];//input query answer buffer.
void tarjan(int u, int p) {// rooted-tree.
    parent[u] = u;
    for(int i = 0; i < tree[u].size(); i++) {//son node.
		int v = tree[u][i].y;
    	if(v == p)	continue;
        tarjan(v, u);
        parent[findp(v)] = u;
    }
    visited[u] = 1;
    for(int i = 0; i < Q[u].size(); i++) {
        if(visited[Q[u][i].second]) {
            LCA[Q[u][i].first] = findp(Q[u][i].second);
        }
    }
}

int query(int x, int y, int lca) {
	int hx = treeLevel[x], hy = treeLevel[y], hlca = treeLevel[lca];
	int ret = 0x3f3f3f3f;
    for(int i = 16; i >= 0; i--) {
        if (hx-hlca >= (1<<i)) {
			ret = min(ret, dp[x][i]);
			x = dpw[x][i];
			hx -= (1<<i);
		}
        if (hy - hlca >= (1<<i)) {
			ret = min(ret, dp[y][i]);
			y = dpw[y][i];
			hy -= (1<<i);
		}
	}
	return ret;
}
int main() {
    //	freopen("in.txt", "r+t", stdin);
    //	freopen("out.txt", "w+t", stdout);
    int n, m, q, x, y;
    while(scanf("%d %d %d", &n, &m, &q) == 3) {
        
        for(int i = 0; i < m; i++) {
        	scanf("%d %d %d", &D[i].x, &D[i].y, &D[i].v);
        }
        
		kruscal(n, m);
		memset(dp, 0, sizeof(dp));
		memset(dpw, 0, sizeof(dpw));
		dfs(1, -1, 1);
        
        for (int i = 1; i <= n; i++)
            visited[i] = 0, Q[i].clear();
        
        vector< pair<int, int> > ask;
        for (int i = 0; i < q; i++) {
        	scanf("%d %d", &x, &y);
        	Q[x].push_back(make_pair(i, y));
        	Q[y].push_back(make_pair(i, x));
            ask.push_back(make_pair(x, y));
		}
		tarjan(1, -1);
        
        for (int i = 0; i < q; i++) {
//            printf("%d %d %d\n", ask[i].first, ask[i].second, LCA[i]);
            printf("%d\n", query(ask[i].first, ask[i].second, LCA[i]));
        }
	}
    return 0;
}
/*
 4 5 4
 1 2 9
 1 3 0
 2 3 8
 2 4 7
 3 4 4
 1 4
 2 1
 3 1
 4 3
 4 5 2
 1 2 30
 2 3 20
 3 4 10
 4 1 40
 2 4 50
 1 3
 1 2
 */
