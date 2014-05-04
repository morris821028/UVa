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
        return  v < a.v;
    }
};
E D[1000005];
vector<E> tree[1005];
int p[1005], rank[1005];
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
double kruscal(int n, int m) {
    double sum = 0;
    
    sort(D, D+m);
    for(int i = 0; i < n; i++) {
        p[i] = i, rank[i] = 1;
        tree[i].clear();
    }
    
    for(int i = 0; i < m; i++) {
        if(joint(D[i].x, D[i].y)) {
        	sum += sqrt(D[i].v);
        	tree[D[i].x].push_back(E(D[i].x, D[i].y, D[i].v));
        	tree[D[i].y].push_back(E(D[i].y, D[i].x, D[i].v));
        }
    }
    return sum;
}
int visited[1005];
double maxEdge[1005][1005];
void dfs(int u, int n) {
	visited[u] = 1;
	for(int i = 0; i < tree[u].size(); i++) {
		int v = tree[u][i].y;
		if(visited[v])	continue;
		double cost = sqrt(tree[u][i].v);
		maxEdge[u][v] = maxEdge[v][u] = cost;
		for(int j = 0; j < n; j++) {
			if(visited[j]) {
				maxEdge[j][v] = maxEdge[v][j] = max(maxEdge[j][u], cost);
			}
		}
		dfs(v, n);
	}
}
int main() {
    int testcase;
    scanf("%d", &testcase);
    while(testcase--) {
        int n, e;
        int X[1005], Y[1005], P[1005];
        scanf("%d", &n);
        for(int i = 0; i < n; i++)
        	scanf("%d %d %d", &X[i], &Y[i], &P[i]);
        e = 0;
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                D[e++] = E(i, j, (X[i] - X[j])*(X[i] - X[j]) 
									+ (Y[i] - Y[j])*(Y[i] - Y[j]));
			}
		}
		double mstcost = kruscal(n, e);
		double ret = 0;
		
		for(int i = 0; i < n; i++)
			visited[i] = 0;
		dfs(0, n);
		
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				ret = max(ret, (P[i] + P[j])/(mstcost - maxEdge[i][j]));
			}
		}
		printf("%.2lf\n", ret);
    }
    return 0;
}
