#include <bits/stdc++.h>
using namespace std;
#define eps 1e-12
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
    double dist2(Pt a) {
    	return (x - a.x)*(x - a.x)+(y - a.y)*(y - a.y);
    }
    double dist(Pt a) {
    	return hypot(x-a.x, y-a.y);
    }
    void read() {
    	scanf("%lf %lf", &x, &y);
    }
    void print() {
    	printf("%.3lf %.3lf", x, y);
    }
};
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
int cmpZero(double x) {
	if (fabs(x) < eps)	return 0;
	return x < 0 ? -1 : 1;
}
const double INF = 1e+30;
Pt city[128][4];
double Ti[128];
double dist[1024];

double dijkstra(int st, int ed, int n, int n_c, double T) {
typedef pair<double, int> PLL;
	for (int i = 0; i <= n; i++)
		dist[i] = INF;
	double w;
	set<PLL> pQ;
	PLL u;
	pQ.insert(PLL(0, st)), dist[st] = 0;
	while (!pQ.empty()) {
		u = *pQ.begin(), pQ.erase(pQ.begin());
		int c = u.second/4, ci = u.second%4;
		int d, di;
		for (int i = 0; i < 4; i++) {
			if (i == ci)
				continue;
			d = c, di = (i)%4, w = (city[c][ci].dist(city[d][di]))*Ti[c];
			if (dist[d*4 + di] > dist[c*4 + ci] + w) {
				if (dist[d*4 + di] != INF)
					pQ.erase(pQ.find(PLL(dist[d*4 + di], d*4 + di)));
				dist[d*4 + di] = dist[c*4 + ci] + w;
				pQ.insert(PLL(dist[d*4 + di], d*4 + di));
			}
		}
		for (int i = 1; i <= n_c; i++) {
			if (i == c) 
				continue;
			for (int j = 0; j < 4; j++) {
				d = i, di = j, w = (city[c][ci].dist(city[d][di]))*T;
				if (dist[d*4 + di] > dist[c*4 + ci] + w) {
					if (dist[d*4 + di] != INF)
						pQ.erase(pQ.find(PLL(dist[d*4 + di], d*4 + di)));
					dist[d*4 + di] = dist[c*4 + ci] + w;
					pQ.insert(PLL(dist[d*4 + di], d*4 + di));
				}
			}
		}
	}
	return dist[ed];
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int S, T, A, B;
		scanf("%d %d %d %d", &S, &T, &A, &B);
		for (int i = 1; i <= S; i++) {
			Pt p[4];
			for (int j = 0; j < 3; j++)
				p[j].read();
			scanf("%lf", &Ti[i]);
			for (int j = 0; j < 3; j++) {
				if (dot(p[(j+2)%3] - p[j], p[(j+1)%3] - p[j]) == 0) {
					city[i][0] = p[(j+2)%3];
					city[i][1] = p[j];
					city[i][2] = p[(j+1)%3];
					city[i][3] = p[j] + (((p[(j+2)%3] + p[(j+1)%3]) * 0.5) - p[j]) * 2;
				}
			}
		}
		
		double ret = INF;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret = min(ret, dijkstra(A*4+i, B*4+j, (S+1)*4, S, T));
			}
		}
		printf("%.2lf\n", ret);
	}
	return 0;
}
