#include <stdio.h>
#include <math.h>
#include <vector>
#include <string.h>
#include <algorithm>
using namespace std;
#define eps 1e-8
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)	return x < a.x;
        return y < a.y;
    }
    bool operator==(const Pt &a) const {
        return fabs(x-a.x) < eps && fabs(y-a.y) < eps;
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator/(const double val) const {
        return Pt(x / val, y / val);
    }
    Pt operator*(const double val) const {
        return Pt(x * val, y * val);
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
Pt D[1024], E[1024];
double Er[1024];
#define maxL (1048576>>5)+1
#define GET(x) (g[(x)>>5]>>((x)&31)&1)
#define SET(x) (g[(x)>>5] |= 1<<((x)&31))
int g[maxL];
void buildGraph(int n, int m) {
	memset(g, 0, sizeof(g));// all link
	sort(D, D+n); // let (i, j) i < j for polar angle in [-pi/2, pi/2]
	for(int i = 0; i < n; i++) {
		vector< pair<double, int> > A;
		for(int j = i+1; j < n; j++)
			A.push_back(make_pair(atan2(D[j].y - D[i].y, D[j].x - D[i].x), j));
		sort(A.begin(), A.end());
		for(int j = 0; j < m; j++) { // test obstacle
			double mm = atan2(E[j].y - D[i].y, E[j].x - D[i].x);
			double theta = asin(Er[j] / dist(E[j], D[i])), L = mm - theta, R = mm + theta;
			int st = lower_bound(A.begin(), A.end(), make_pair(L, -1)) - A.begin();
			for(int k = st; k < A.size() && A[k].first <= R; k++) {
				if(dot(D[i] - D[A[k].second], E[j] - D[A[k].second]) > 0)
					SET(i * n + A[k].second), SET(A[k].second * n + i);
			}
		}
	}
}
int visited[1024];
void dfs(int u, int n) {
	visited[u] = 1;
	for(int i = 0; i < n; i++) {
		if(!GET(u * n + i) && !visited[i]) {
			dfs(i, n);
		}
	}
}
int main() {
	int testcase, n, m;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &m);
		for(int i = 0; i < n; i++) 
			scanf("%lf %lf", &D[i].x, &D[i].y);
		for(int i = 0; i < m; i++)
			scanf("%lf %lf %lf", &E[i].x, &E[i].y, &Er[i]);
		buildGraph(n, m);
		int ret = 0;
		memset(visited, 0, sizeof(visited));
		for(int i = 0; i < n; i++) // compute how many component
			if(visited[i] == 0)
				dfs(i, n), ret++;
		printf("%d\n", ret - 1);
	}
	return 0;
}
/*
2
6 3
1 8
5 4
7 7
9 2
16 6
17 10
4 7 2
6 3 1
12 6 3

4 4
0 4
8 4
4 0
4 8
2 2 1
6 2 1
2 6 1
6 6 1
*/
