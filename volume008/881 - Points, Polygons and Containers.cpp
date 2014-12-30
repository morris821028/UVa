#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <iostream>
#include <assert.h>
using namespace std;

#define eps 1e-8
#define MAXN 1024
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}	
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    bool operator<(const Pt &a) const {
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	bool operator==(const Pt &a) const {
		return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	} 
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
double cross2(Pt a, Pt b) {
    return a.x * b.y - a.y * b.x;
}
int between(Pt a, Pt b, Pt c) {
	return dot(c - a, b - a) >= -eps && dot(c - b, a - b) >= -eps;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int inPolygon(Pt p[], int n, Pt q) {
	int i, j, cnt = 0;
	for(i = 0, j = n-1; i < n; j = i++) {
		if(onSeg(p[i], p[j], q))
			return 1;
		if(p[i].y > q.y != p[j].y > q.y &&
			q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
			cnt++;
	}
	return cnt&1;
}
const double pi = acos(-1);
Pt polygon[MAXN][512];
int pn[MAXN], parent[MAXN], visited[MAXN], depth[MAXN];
int pid[MAXN];
vector<int> g[MAXN], tree[MAXN];
void dfs(int u) {
	visited[u] = 1, depth[u] = 0, parent[u] = -1;
	int d = -1;
	for (int i = 0; i < g[u].size(); i++) {
		int v = g[u][i];
		if (visited[v] == 0)	dfs(v);
		if (depth[v] > d)
			d = depth[v], parent[u] = v;
	}
	depth[u] = d + 1;
}
int query(int u, Pt q) {
	for (int i = 0; i < tree[u].size(); i++) {
		int v = tree[u][i];
		if (inPolygon(polygon[v], pn[v], q)) {
			return query(v, q);
		}
	}
	return u;
}
int main() {
	int testcase, n, m;
	string line;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		assert(n < MAXN);
		while (getchar() != '\n');
		for (int i = 0; i < n; i++) {
			getline(cin, line);
			stringstream sin(line);
			int m = 0;
			sin >> pid[i];
			while (sin >> polygon[i][m].x >> polygon[i][m].y) {
				m++;
				assert(m < 512);
			}
			pn[i] = m;
		}
		pid[n] = 0;
		for (int i = 0; i <= n; i++)
			g[i].clear(), visited[i] = 0, tree[i].clear();
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j)	continue;
				if (inPolygon(polygon[i], pn[i], polygon[j][0]))
					g[j].push_back(i);
			}
		}
		
		for (int i = 0; i < n; i++) {
			if (visited[i] == 0)
				dfs(i);
		}
		for (int i = 0; i < n; i++)
			if (parent[i] == -1)
				tree[n].push_back(i);
			else
				tree[parent[i]].push_back(i);
//		for (int i = 0; i < n; i++)
//			printf("%d: %d\n", pid[i], parent[i]);
		scanf("%d", &m);
		assert(m < 32767);
		int out[32767] = {};
		for (int i = 0; i < m; i++) {
			Pt q;
			int id;
			scanf("%d %lf %lf", &id, &q.x, &q.y);
			assert(id <= m);
			out[id] = query(n, q);
		}
		for (int i = 1; i <= m; i++)
			printf("%d %d\n", i, pid[out[i]]);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
5
0 0
50 50
100 0
100 100
0 100
2
49 50
50 51

7
0 5
5 0
10 7
15 0
20 5
15 10
5 10
7
0 5
5 0
10 7
15 0
20 5
15 10
5 10

*/
