#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
#include <string.h>
#include <list>
using namespace std;

#define eps 1e-8
#define MAXV 131072
#define MAXD 20
struct Point {
    double x, y;
    int id;
    Point(double a = 0, double b = 0, int c = -1):
    	x(a), y(b), id(c) {}	
	Point operator-(const Point &a) const {
        return Point(x - a.x, y - a.y);
    }
    Point operator+(const Point &a) const {
        return Point(x + a.x, y + a.y);
    }
    Point operator*(const double a) const {
        return Point(x * a, y * a);
    }
	Point operator/(const double a) const {
        return Point(x / a, y / a);
    }
    bool operator<(const Point &a) const {
		if (fabs(x - a.x) > eps)	return x < a.x;
		if (fabs(y - a.y) > eps)	return y < a.y;
		return false;
	}
	bool operator==(const Point &a) const {
		return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
	bool operator!=(const Point &a) const {
		return !(fabs(x - a.x) < eps && fabs(y - a.y) < eps);
	} 
	void read(int id = -1) {
		this->id = id;
	}
	double dist(Point b) {
		return hypot(x - b.x, y - b.y);
	}
	double dist2(Point b) {
		return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
	}
	void print() {
		printf("point (%lf, %lf)\n", x, y);
	}
};
struct Point3D {
	double x, y, z;
	Point3D(double a = 0, double b = 0, double c = 0):
		x(a), y(b), z(c) {}
	Point3D(Point p) {
		x = p.x, y = p.y, z = p.x * p.x + p.y * p.y;
	}
	Point3D operator-(const Point3D &a) const {
        return Point3D(x - a.x, y - a.y, z - a.z);
    }
    double dot(Point3D a) {
    	return x * a.x + y * a.y + z * a.z;
    }
};
struct Edge {
	int id;
	list<Edge>::iterator twin;
	Edge(int id = 0) {
		this->id = id;
	}
};

int cmpZero(double v) {
	if (fabs(v) > eps)	return v > 0 ? 1 : -1;
	return 0;
}

double cross(Point o, Point a, Point b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
Point3D cross(Point3D a, Point3D b) { // normal vector
    return Point3D(a.y * b.z - a.z * b.y 
				 , -a.x * b.z + a.z * b.x
				 , a.x * b.y - a.y * b.x);
}
int inCircle(Point a, Point b, Point c, Point p) {
	if (cross(a, b, c) < 0)
		swap(b, c);
	Point3D a3(a), b3(b), c3(c), p3(p);
//	printf("%lf %lf %lf\n", a3.x, a3.y, a3.z);
//	printf("%lf %lf %lf\n", b3.x, b3.y, b3.z);
//	printf("%lf %lf %lf\n", c3.x, c3.y, c3.z);
//	printf("%lf %lf %lf\n", p3.x, p3.y, p3.z);
	b3 = b3 - a3, c3 = c3 - a3, p3 = p3 - a3;
	Point3D f = cross(b3, c3); // normal vector
	return cmpZero(p3.dot(f)); // check same direction, in: < 0, on: = 0, out: > 0
}
int intersection(Point a, Point b, Point c, Point d) { // seg(a, b) and seg(c, d)
	return cmpZero(cross(a, c, b)) * cmpZero(cross(a, b, d)) > 0 
		&& cmpZero(cross(c, a, d)) * cmpZero(cross(c, d, b)) > 0;
}
class Delaunay {
	public:
	list<Edge> head[MAXV]; // graph
	Point p[MAXV];
	int n, rename[MAXV];
	void init(int n, Point p[]) {
		for (int i = 0; i < n; i++)
			head[i].clear();
		for (int i = 0; i < n; i++)
			this->p[i] = p[i];
		sort(this->p, this->p + n);
		for (int i = 0; i < n; i++)
			rename[p[i].id] = i;
		this->n = n;
		divide(0, n - 1);
	}
	void addEdge(int u, int v) {
		head[u].push_front(Edge(v));
		head[v].push_front(Edge(u));
		head[u].begin()->twin = head[v].begin();
		head[v].begin()->twin = head[u].begin();
	}
	void divide(int l, int r) {
		if (r - l <= 2) { // #point <= 3
			for (int i = l; i <= r; i++)
				for (int j = i+1; j <= r; j++)
					addEdge(i, j); 
			return;
		}
		int mid = (l + r) /2;
		divide(l, mid);
		divide(mid + 1, r);
		
		list<Edge>::iterator it;
		int nowl = l, nowr = r;
		
//		printf("divide %d %d\n", l, r);
		for (int update = 1; update; ) { // find left and right convex, lower common tangent
			update = 0;
			Point ptL = p[nowl], ptR = p[nowr];
			for (it = head[nowl].begin(); it != head[nowl].end(); it++) {
				Point t = p[it->id];
				double v = cross(ptR, ptL, t);
				if (cmpZero(v) > 0 || (cmpZero(v) == 0 && ptR.dist2(t) < ptR.dist2(ptL))) {
					nowl = it->id, update = 1;
					break;
				}
			}
			if (update)	continue;
			for (it = head[nowr].begin(); it != head[nowr].end(); it++) {
				Point t = p[it->id];
				double v = cross(ptL, ptR, t);
				if (cmpZero(v) < 0 || (cmpZero(v) == 0 && ptL.dist2(t) < ptL.dist2(ptR))) {
					nowr = it->id, update = 1;
					break;
				}
			}
		}
		
		addEdge(nowl, nowr); // add tangent
//		printf("add base %d %d\n", nowl, nowr);
		for (int update = 1; true;) {
			update = 0;
			Point ptL = p[nowl], ptR = p[nowr];
			int ch = -1, side = 0;
			for (it = head[nowl].begin(); it != head[nowl].end(); it++) {
//				ptL.print(), ptR.print(), p[it->id].print();
				if (cmpZero(cross(ptL, ptR, p[it->id])) > 0
					&& (ch == -1 || inCircle(ptL, ptR, p[ch], p[it->id]) < 0))
					ch = it->id, side = -1;
//				printf("test L %d %d %d\n", nowl, it->id, inCircle(ptL, ptR, p[ch], p[it->id]));
			}
			for (it = head[nowr].begin(); it != head[nowr].end(); it++) {
				if (cmpZero(cross(ptR, p[it->id], ptL)) > 0
					&& (ch == -1 || inCircle(ptL, ptR, p[ch], p[it->id]) < 0))
					ch = it->id, side = 1;
//				printf("test R %d %d %d\n", nowr, it->id, inCircle(ptL, ptR, p[ch], p[it->id])); 
			}
			if (ch == -1)	break; // upper common tangent
//			printf("choose %d %d\n", ch, side);
			if (side == -1) {
				for (it = head[nowl].begin(); it != head[nowl].end(); ) {
					if (intersection(ptL, p[it->id], ptR, p[ch])) {
						head[it->id].erase(it->twin);
						head[nowl].erase(it++);
					} else
						it++;
				}
				nowl = ch;
				addEdge(nowl, nowr);
			} else {
				for (it = head[nowr].begin(); it != head[nowr].end(); ) {
					if (intersection(ptR, p[it->id], ptL, p[ch])) {
						head[it->id].erase(it->twin);
						head[nowr].erase(it++);
					} else
						it++;
				}
				nowr = ch;
				addEdge(nowl, nowr);
			}
		}
	}
	
	vector< pair<int, int> > getEdge() {
		vector< pair<int, int> > ret;
		list<Edge>::iterator it;
		for (int i = 0; i < n; i++) {
			for (it = head[i].begin(); it != head[i].end(); it++) {
				if (it->id < i)
					continue;
//				printf("DG %d %d\n", i, it->id);
				ret.push_back(make_pair(p[i].id, p[it->id].id));
			}
		}
		return ret;
	}
} tool;

struct edge {
	int x, y, v;
	edge(int a = 0, int b = 0, int c = 0):
		x(a), y(b), v(c) {}
	bool operator<(const edge &a) const {
		return v < a.v;
	}
};

class MST {
	public:
	vector<edge> tree[MAXV];
	int parent[MAXV], weight[MAXV];
	int visited[MAXV], depth[MAXV];
	int dp[MAXV][MAXD], dpParent[MAXV][MAXD];
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
	int kruscal(int n, vector<edge> D) {
	    int sum = 0, e = 0;
	    
	    sort(D.begin(), D.end());
	    for(int i = 0; i <= n; i++) {
	        parent[i] = i, weight[i] = 1;
	        tree[i].clear();
	    }
	    
	    for(int i = 0; i < D.size() && e < n - 1; i++) {
	        if(joint(D[i].x, D[i].y)) {
	        	sum += D[i].v, e++;
	        	tree[D[i].x].push_back(edge(D[i].x, D[i].y, D[i].v));
	        	tree[D[i].y].push_back(edge(D[i].y, D[i].x, D[i].v));
//	        	printf("mst %d %d %d\n", D[i].x, D[i].y, D[i].v);
	        }
	    }
	    return sum;
	}
	void doubling(int n) {
		for(int i = 0; i <= n; i++)
			visited[i] = 0, memset(dpParent[i], 0, sizeof(dpParent[i]));
		queue<int> Q;
		int u, v;
		Q.push(0), depth[0] = 0, visited[0] = 1;
		dpParent[0][0] = -1;
		while (!Q.empty()) {
			u = Q.front(), Q.pop();
			for (int i = 0; i < tree[u].size(); i++) {
				v = tree[u][i].y;
				if (!visited[v]) {
					depth[v] = depth[u] + 1;
					dp[v][0] = tree[u][i].v, dpParent[v][0] = u;
					visited[v] = 1;
					Q.push(v);
				}
			}
			for (int i = 0; dpParent[u][i]; i++) {
				dp[u][i+1] = max(dp[u][i], dp[dpParent[u][i]][i]);
				dpParent[u][i+1] = dpParent[dpParent[u][i]][i];
			}
		}
	}
	int queryPath(int u, int v) {
		int ret = 0;
		if (depth[u] < depth[v])	swap(u, v);
		int dist = depth[u] - depth[v];
		for (int i = 0; dist; i++, dist /= 2) {
			if (dist&1) {
				ret = max(ret, dp[u][i]);
				u = dpParent[u][i];
			}
		}
		for (int i = 0; u != v; ) {
			if (dpParent[u][i] != dpParent[v][i] || (i == 0 && dpParent[u][i] == dpParent[v][i])) {
				ret = max(ret, dp[u][i]);
				u = dpParent[u][i];
				ret = max(ret, dp[v][i]);
				v = dpParent[v][i];
				i++;
			} else {
				i--;
			}
		}
		return ret;
	}
} mst;
	
Point p[MAXV];
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n, m, q, cases = 0;
	int x, y;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			p[i] = Point(x, y, i);
		}
		
		tool.init(n, p);
		
		vector<edge> E;
		vector< pair<int, int> > DG = tool.getEdge();
		for (int i = 0; i < DG.size(); i++) {
			x = DG[i].first, y = DG[i].second;
			int v = (p[x].x - p[y].x) * (p[x].x - p[y].x) + 
						(p[x].y - p[y].y) * (p[x].y - p[y].y);
			E.push_back(edge(x, y, v));
		}
		
		mst.kruscal(n, E); 	// build MST
		mst.doubling(n); 	// doubling algorithm
		
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &x, &y);
			x--, y--;
			double ret = mst.queryPath(x, y);
			printf("%.10lf\n", sqrt(ret));
		}
	}
	return 0;
}
/*
3
0 0
50 10
150 0
3
1 2
1 3
2 3
*/
