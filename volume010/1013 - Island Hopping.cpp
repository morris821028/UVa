#include <stdio.h> 
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 64;
double X[MAXN], Y[MAXN], M[MAXN];
struct Edge {
	int x, y;
	double v;
	Edge(int a = 0, int b = 0, double c = 0):
		x(a), y(b), v(c) {}
	bool operator<(const Edge &x) const {
		return v < x.v;
	}
};
vector<Edge> E;
int parent[MAXN], weight[MAXN];
double weight2[MAXN];
int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
}
int joint(int x, int y) {
	x = findp(x), y = findp(y);
	if (x == y)	
		return 0;
	if (weight[x] > weight[y]) {
		parent[y] = x, weight[x] += weight[y];
		weight2[x] += weight2[y];
	} else {
		parent[x] = y, weight[y] += weight[x];
		weight2[y] += weight2[x];
	}
	return 1;
}
double solve(int n) {
	sort(E.begin(), E.end());
	double div = 0, sum = 0;
	int u, v;
	for (int i = 0; i < n; i++)
		parent[i] = i, weight[i] = 1, weight2[i] = M[i], div += M[i];
		
	for (int i = 0; i < E.size(); i++) {
		u = E[i].x, v = E[i].y;
		if (findp(u) != findp(v)) {
			if (findp(u) == findp(0))
				sum += weight2[findp(v)] * E[i].v;
			if (findp(v) == findp(0))
				sum += weight2[findp(u)] * E[i].v;
			joint(u, v);
		}
	}
	return sum / div;
}
int main() {
	int n, cases = 0;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++)
			scanf("%lf %lf %lf", &X[i], &Y[i], &M[i]);
		E.clear();
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++) {
				double v = hypot(X[i] - X[j], Y[i] - Y[j]);
				E.push_back(Edge(i, j, v));
			}
		}
		
		double ret = solve(n);
		
		printf("Island Group: %d Average %.2lf\n", ++cases, ret);
		
		puts("");
	}
	return 0;
}
/*
7
11 12 2500
14 17 1500
9 9 750
7 15 600
19 16 500
8 18 400
15 21 250
0
*/
