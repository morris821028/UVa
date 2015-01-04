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
#define MAXN 64
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
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
int intersection(Pt a, Pt b, Pt c, Pt d) { // seg(a, b) and seg(c, d)
	return cmpZero(cross(a, c, b)) * cmpZero(cross(a, b, d)) > 0
		&& cmpZero(cross(c, a, d)) * cmpZero(cross(c, d, b)) > 0;
}
int parent[MAXN], weight[MAXN];
int findp(int x) {
	return parent[x] == x ? x : parent[x] = findp(parent[x]);
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
int main() {
	int n, pn[MAXN];
	char line[32767];
	Pt polygon[MAXN][512];
	while (scanf("%d", &n) == 1 && n) {
		while (getchar() != '\n');
		for (int i = 0; i < n; i++) {
			gets(line);
			stringstream sin(line);
			int m = 0;
			while (sin >> polygon[i][m].x >> polygon[i][m].y)
				m++;
			pn[i] = m;
		}
		for (int i = 0; i < n; i++)
			parent[i] = i, weight[i] = 1;
			
		int ret = n;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (findp(i) == findp(j))	continue;
				for (int k = 0; k < pn[j]; k++) {
					if (inPolygon(polygon[i], pn[i], polygon[j][k])) {
						ret -= joint(i, j);
						break;
					}
				}
			}
		}
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (findp(i) == findp(j))	continue;
				for (int p = 0, q = pn[i] - 1; p < pn[i]; q = p++) {
					for (int a = 0, b = pn[j] - 1; a < pn[j]; b = a++) {
						if (intersection(polygon[i][p], polygon[i][q], polygon[j][a], polygon[j][b])) {
							ret -= joint(i, j);
							break;
						}
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
