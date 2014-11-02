#include <stdio.h>
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
using namespace std;
#define eps 1e-6
struct Pt {
    double x, y;
	int  label;
    Pt(double a = 0, double b = 0, int c = 0):
    	x(a), y(b), label(c) {}
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)	return x < a.x;
        if (fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(Pt a, Pt b, Pt c) {
	return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs) * cross(as, at, bt) < 0 &&
       cross(at, as, bs) * cross(at, as, bt) < 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) < 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) < 0)
        return 1;
    return 0;
}
// this problem
vector<int> g[512];

struct Polygon { // convex
	vector<Pt> p;
	int contain(Polygon &a) {
		int n = p.size();
		if(n < 3)	return false;
		Pt q = a.p[0];
		if(cross(p[0], q, p[1]) > eps)		return 0;
		if(cross(p[0], q, p[n-1]) < -eps)	return 0;
		int l = 2, r = n - 1;
		int line = -1;
		while(l <= r) {
			int mid = (l + r)>>1;
			if(cross(p[0], q, p[mid]) > -eps) {
				line = mid;
				r = mid - 1;
			} else l = mid + 1;
		}
		return cross(p[line-1], q, p[line]) < eps;
	}
};
Polygon poly[512];

int parent[32767], visited[32767], depth[32767];
void bfs(int u) {
	int v;
	queue<int> Q;
	Q.push(u);
	visited[u] = 1, depth[u] = 1;
	while (!Q.empty()) {
		u = Q.front(), Q.pop();
		for (int i = 0; i < g[u].size(); i++) {
			v = g[u][i];
			if (depth[v] < depth[u] + 1) {
				depth[v] = depth[u] + 1;
				visited[v] = 1, parent[v] = u;
				Q.push(v);
			}
		}
	}
}
int main() {
	int N, M, cases = 0;
	while(scanf("%d", &N) == 1 && N) {
		for(int i = 0; i < N; i++) {
			scanf("%d", &M);
			poly[i].p.resize(M);
			for (int j = 0; j < M; j++)
				scanf("%lf %lf", &poly[i].p[j].x, &poly[i].p[j].y);
			double mnx = poly[i].p[0].x;
			int idx = 0;
			for (int j = 0; j < M; j++) {
				if (poly[i].p[j].x < mnx)
					mnx = poly[i].p[j].x, idx = j;
			}
			if (cross(poly[i].p[idx], poly[i].p[(idx+1)%M], poly[i].p[(idx-1+M)%M]) < eps)
				reverse(poly[i].p.begin(), poly[i].p.end());
		}
		
		for (int i = 0; i < N; i++)
			g[i].clear();
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)	continue;
				if (poly[i].contain(poly[j]))
					g[i].push_back(j);
			}
		}
		
		for (int i = 0; i < N; i++) {
			visited[i] = 0, parent[i] = -1, depth[i] = 0;
		}
		for (int i = 0; i < N; i++) {
			if (visited[i] == 0)
				bfs(i);
		}		
		int communities = 0;
		double Acost = 0, Bcost = 0;
		for (int i = 0; i < N; i++) {
			if (parent[i] == -1)
				communities++;
			double tmp = 0;
			for (int j = 0, k = poly[i].p.size() - 1; j < poly[i].p.size(); k = j++)
				tmp += dist(poly[i].p[j], poly[i].p[k]);
			if (depth[i]&1)
				Acost += tmp;
			else
				Bcost += tmp/2;
		}
		
		printf("Case %d:\n", ++cases);
		printf("Total Number of Communities %d\n", communities);
		printf("Total Cost:\n");
		printf("Steel Fence: %.8lf Million Yuan\n", Acost / 10000.0);
		printf("Wooden Fence: %.8lf Million Yuan\n", Bcost / 10000.0);
		puts("");
	}
	return 0;
}
/*
8
8 112 134 73 141 41 119 32 82 54 50 92 43 124 65 132 103
6 119 119 102 119 94 101 102 83 119 83 127 101
8 83 106 62 111 45 99 42 78 54 59 75 55 92 66 96 87
6 70 97 56 97 49 85 56 73 70 73 77 85
8 143 222 110 244 61 238 35 209 39 169 72 147 121 153 147 181
4 115 226 58 226 51 167 132 167
4 113 212 65 212 65 172 113 172
5 99 205 83 206 71 187 91 179 105 189

2
4 0 0 100 0 100 100 0 100
4 1000 1000 1100 1000 1100 1100 1000 1100
0
*/
