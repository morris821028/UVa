#include <bits/stdc++.h> 
using namespace std;
#define eps 1e-12
struct Point {
    double x, y;
    Point(double a = 0, double b = 0):
    x(a), y(b) {}
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
    Point3D operator-(const Point3D &a) const {
        return Point3D(x - a.x, y - a.y, z - a.z);
    }
    double dot(Point3D a) {
        return x * a.x + y * a.y + z * a.z;
    }
    void print() {
    	printf("%.1lf %.1lf %.1lf\n", x, y, z);
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
    return Point3D(a.y*b.z - a.z*b.y, -a.x*b.z + a.z*b.x, a.x*b.y - a.y*b.x);
}
double area(Point3D x, Point3D y, Point3D z) {
	Point3D m = y - x, n = z - x;
	double a, b, c, p, q, r, area;
	a = m.x, b = m.y, c = m.z;
	p = n.x, q = n.y, r = n.z;
	area = sqrt(pow(b*r-c*q, 2)+pow(c*p-a*r, 2)+pow(a*q-b*p, 2)) / 2.0;
	return area;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		double x, y, z;
		Point3D A[32], B[32];
		scanf("%d %d %lf", &n, &m, &z);
		for (int i = 0; i < n; i++)
			scanf("%lf %lf", &x, &y), A[i] = Point3D(x, y, 0), A[i+n] = A[i];
		for (int i = 0; i < m; i++)
			scanf("%lf %lf", &x, &y), B[i] = Point3D(x, y, z), B[i+m] = B[i];
		
		double ret = 1e+30;
		for (int st = 0; st < n; st++) {
			double dp[64][64];
			for (int i = 0; i <= 2*n; i++)
				for (int j = 0; j <= m; j++)
					dp[i][j] = 1e+10;
			dp[st][1] = area(A[st], B[0], B[1]);
			for (int i = 1; i <= m; i++) {
				for (int j = 0; j < 2*n; j++)  {
					if (dp[j][i] >= 1e+10)
						continue;
					dp[j+1][i] = min(dp[j+1][i], dp[j][i] + area(A[j], A[j+1], B[i]));
					dp[j][i+1] = min(dp[j][i+1], dp[j][i] + area(A[j], B[i], B[i+1]));
				}
			}
			ret = min(ret, dp[st+n][m]);
		}
		printf("%.5lf\n", ret);
	}
	return 0;
}
/*
2

4 3 1
0 0
1 0
1 1
0 1
0 0
1 0
0.5 1

4 4 2
0 0
1 0
1 1
0 1
0 0
1 0
1 1
0 1
*/
