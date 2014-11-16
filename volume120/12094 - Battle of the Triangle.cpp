#include <stdio.h> 
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
#define eps 1e-6
const double pi = acos(-1); 
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)
            return x < a.x;
        return y < a.y;
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator*(const double &a) const {
        return Pt(x * a, y * a);
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double length(Pt a) {
	return hypot(a.x, a.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}
double angle(Pt a, Pt b) {
	return acos(dot(a, b) / length(a) / length(b));
}
Pt rotateRadian(Pt a, double radian) {
	double x, y;
	x = a.x * cos(radian) - a.y * sin(radian);
	y = a.x * sin(radian) + a.y * cos(radian);
	return Pt(x, y);
}
Pt getIntersection(Pt p, Pt l1, Pt q, Pt l2) {
	double a1, a2, b1, b2, c1, c2;
	double dx, dy, d;
	a1 = l1.y, b1 = -l1.x, c1 = a1 * p.x + b1 * p.y;
	a2 = l2.y, b2 = -l2.x, c2 = a2 * q.x + b2 * q.y;
	d = a1 * b2 - a2 * b1;
	dx = b2 * c1 - b1 * c2;
	dy = a1 * c2 - a2 * c1;
	return Pt(dx / d, dy / d);
}
struct Line {
	int A, B, C;
	bool operator<(const Line &a) const {
		double t1 = atan2(B, A);
		double t2 = atan2(a.B, a.A);
		if (t1 < 0)	t1 += pi;
		if (t2 < 0)	t2 += pi;
		return t1 < t2;
	}
};
Pt getIntersection(Line l1, Line l2) {
	double a1, a2, b1, b2, c1, c2;
	double dx, dy, d;
	a1 = l1.A, b1 = l1.B, c1 = -l1.C;
	a2 = l2.A, b2 = l2.B, c2 = -l2.C;
	d = a1 * b2 - a2 * b1;
	dx = b2 * c1 - b1 * c2;
	dy = a1 * c2 - a2 * c1;
	return Pt(dx / d, dy / d);
}
struct cmp {
	static Line base;
	bool operator() (const Pt &p1, const Pt &p2) const {
		double c1, c2;
		c1 = p1.x * base.A + p1.y * base.B;
		c2 = p2.x * base.A + p2.y * base.B;
		if (fabs(c1 - c2) > eps)
			return c1 < c2;
		return false;
	}
};
Line cmp::base;
int main() {
	int cases = 0;
	int n, m, q;
	double x, y;
	while (scanf("%d %d %d", &n, &m, &q) == 3 && n) {
		vector<Pt> soldiers, tanks;
		vector<Pt> soldier[3], tank[3];
		Line Q[10000][3];
		for (int i = 0; i < n; i++) {
			scanf("%lf %lf", &x, &y);
			soldiers.push_back(Pt(x, y));
		}
		for (int i = 0; i < m; i++) {
			scanf("%lf %lf", &x, &y);
			tanks.push_back(Pt(x, y));
		}
		for (int i = 0; i < q; i++) {
			for (int j = 0; j < 3; j++) {
				scanf("%d %d %d", &Q[i][j].A, &Q[i][j].B, &Q[i][j].C);
				if (Q[i][j].A < 0 || (Q[i][j].A == 0 && Q[i][j].B < 0)) {
					Q[i][j].A = -Q[i][j].A;
					Q[i][j].B = -Q[i][j].B;
					Q[i][j].C = -Q[i][j].C;
				}
			}
			sort(Q[i], Q[i] + 3);
		}
		for (int i = 0; i < 3; i++) {
			soldier[i] = soldiers;
			tank[i] = tanks;
			cmp::base = Q[0][i];
			sort(soldier[i].begin(), soldier[i].end(), cmp());
			sort(tank[i].begin(), tank[i].end(), cmp());
		}
//		for (int i = 0; i < 3; i++) {
//			for (int j = 0; j < soldier[i].size(); j++)
//				printf("%.2lf %.2lf ,", soldier[i][j].x, soldier[i][j].y);
//			puts("\n--++--");
//		}
		printf("Battle Field %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
//			for (int j = 0; j < 3; j++)
//				printf("%d %d %d -\n", Q[i][j].A, Q[i][j].B, Q[i][j].C);
			Pt pabc[3];
			pabc[0] = getIntersection(Q[i][1], Q[i][2]); // bc
			pabc[1] = getIntersection(Q[i][0], Q[i][2]); // ac
			pabc[2] = getIntersection(Q[i][0], Q[i][1]); // ab
			int ret1 = 0, ret2 = 0;
			int tmp[3];
			for (int j = 0; j < 3; j++) {
				cmp::base = Q[i][j];
				tmp[j] = (int)(lower_bound(soldier[j].begin(), soldier[j].end(), 
				pabc[(j+1)%3], cmp()) - soldier[j].begin());
				int v1 = (Q[i][j].A * pabc[j].x + Q[i][j].B * pabc[j].y + Q[i][j].C < 0);
				int v2 = (Q[i][j].A * soldier[j][0].x + Q[i][j].B * soldier[j][0].y + Q[i][j].C < 0);
				int v3 = (Q[i][j].A * soldier[j][soldier[j].size()-1].x + Q[i][j].B * soldier[j][soldier[j].size()-1].y + Q[i][j].C < 0);
					
				if (j == 0)  {
					if (tmp[j]) {
						if (v1 != v2)
							tmp[j] = soldier[j].size() - tmp[j];
					} else {
						if (v1 == v3)
							tmp[j] = soldier[j].size() - tmp[j];
					}
				} else {
					if (tmp[j]) {
						if (v1 == v2)
							tmp[j] = soldier[j].size() - tmp[j];
					} else {
						if (v1 != v3)
							tmp[j] = soldier[j].size() - tmp[j];
					}
				}
//				printf("[%d] soldier %d\n", j, tmp[j]);
			}
			ret1 = tmp[0] - tmp[1] - tmp[2];
			for (int j = 0; j < 3; j++) {
				cmp::base = Q[i][j];
				tmp[j] = (int)(lower_bound(tank[j].begin(), tank[j].end(), 
				pabc[(j+1)%3], cmp()) - tank[j].begin());
				int v1 = (Q[i][j].A * pabc[j].x + Q[i][j].B * pabc[j].y + Q[i][j].C < 0);
				int v2 = (Q[i][j].A * tank[j][0].x + Q[i][j].B * tank[j][0].y + Q[i][j].C < 0);
				int v3 = (Q[i][j].A * tank[j][tank[j].size()-1].x + Q[i][j].B * tank[j][tank[j].size()-1].y + Q[i][j].C < 0);
					
				if (j == 0)  {
					if (tmp[j]) {
						if (v1 != v2)
							tmp[j] = tank[j].size() - tmp[j];
					} else {
						if (v1 == v3)
							tmp[j] = tank[j].size() - tmp[j];
					}
				} else {
					if (tmp[j]) {
						if (v1 == v2)
							tmp[j] = tank[j].size() - tmp[j];
					} else {
						if (v1 != v3)
							tmp[j] = tank[j].size() - tmp[j];
					}
				}
//				printf("[%d] tank %d\n", j, tmp[j]);
			}
			ret2 = tmp[0] - tmp[1] - tmp[2];
			printf("Query %d: %d %d\n", i+1, ret1, ret2);
		}
	}
	return 0;
}
/*
8 5 2
-1 8
-7 3
-2 1
-2 -1
-5 -2
6 -1
2 -4
-4 -5
1 7
1 1
3 4
-6 5
-12 -6
2 -2 10
-2 6 6
-5 -3 1
1 -1 5
1 -3 -3
5 3 -15
0 0 0
*/
