#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
struct Pt {
    int x, y;
    Pt() {}
    Pt(int a, int b): x(a), y(b) {}
    Pt operator-(const Pt &a) const { return Pt(x - a.x, y - a.y); }
    Pt operator+(const Pt &a) const { return Pt(x + a.x, y + a.y); }
    Pt operator*(const double a) const { return Pt(x * a, y * a);  }
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)	return x < a.x;
        if (fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
    bool operator==(const Pt &a) const {
        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
    }
};
double dot(Pt a, Pt b) {
    return a.x * b.x + a.y * b.y;
}
int64_t cross(Pt o, Pt a, Pt b) {
    return (int64_t) (a.x-o.x)*(b.y-o.y)- (int64_t) (a.y-o.y)*(b.x-o.x);
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
int cmpZero(float v) {
    if (fabs(v) > eps) return v > 0 ? 1 : -1;
    return 0;
}

const int MAXN = 100005;

pair<int, int> internal_tangent(Pt p[], int pn, Pt q[], int qn, int type) {
	int i = 0, j = 0, update;
	if (type == 0) {
		do {
			update = 0;
			while (cross(p[i], q[j], q[(j+qn-1)%qn]) > 0 || cross(p[i], q[j], q[(j+1)%qn]) > 0) {
				j = (j+1)%qn;
			}
			while (cross(q[j], p[i], p[(i+pn-1)%pn]) > 0 || cross(q[j], p[i], p[(i+1)%pn]) > 0) {
				i = (i+1)%pn, update = 1;
			}
		} while (update);
		if (cross(q[j], p[i], p[(i+1)%pn]) == 0)
			i = (i+1)%pn;
	} else {
		do {
			update = 0;
			while (-cross(p[i], q[j], q[(j+qn-1)%qn]) > 0 || -cross(p[i], q[j], q[(j+1)%qn]) > 0) {
				j = (j+1)%qn;
			}
			while (-cross(q[j], p[i], p[(i+pn-1)%pn]) > 0 || -cross(q[j], p[i], p[(i+1)%pn]) > 0) {
				i = (i+1)%pn, update = 1;
			}
		} while (update);
		if (cross(q[j], p[i], p[(i+pn-1)%pn]) == 0)
			i = (i+pn-1)%pn;
	}
	return {i, j};
}
int main() {
	int cases = 0;
	int n, m;
	int x, y;
	static Pt p[MAXN], q[MAXN];
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			p[i] = Pt(x, y);
		}
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			q[i] = Pt(x, y);
		}

		pair<int, int> l1 = internal_tangent(p, n, q, m, 0);
		pair<int, int> l2 = internal_tangent(p, n, q, m, 1);
//		printf("- %d %d\n", l1.first, l1.second);
//		printf("+ %d %d\n", l2.first, l2.second);
		printf("Instance %d:\n", ++cases);
		if (p[l1.first].x == q[l1.second].x) {
			puts("VERTICAL");
		} else {
			double slope = (double) (p[l1.first].y - q[l1.second].y) / (p[l1.first].x - q[l1.second].x);
			if (fabs(slope) < 9e-4)
				slope = 0;
			printf("%.3lf\n", slope);
		}

		do {
			printf("%d %d\n", p[l1.first].x, p[l1.first].y);
			l1.first = (l1.first+1)%n;
		} while (l1.first != l2.first);
		printf("%d %d\n", p[l2.first].x, p[l2.first].y);

		if (p[l2.first].x == q[l2.second].x) {
			puts("VERTICAL");
		} else {
			double slope = (double) (p[l2.first].y - q[l2.second].y) / (p[l2.first].x - q[l2.second].x);
			if (fabs(slope) < 9e-4)
				slope = 0;
			printf("%.3lf\n", slope);
		}
	}
	return 0;
}

/*
3 3
10 20
20 20
20 10
10 10
7 5
5 7

4 3
20 19
25 15
20 10
15 15
10 20
10 10
5 15

0 0

*/
