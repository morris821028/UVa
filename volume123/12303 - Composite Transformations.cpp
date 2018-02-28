#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
/*
	rotate matrix: http://blog.csdn.net/zsq306650083/article/details/8773996
*/
struct Matrix {
	double v[4][4];
	Matrix(double a=0) {
		memset(v, 0, sizeof(v));
		if (a != 0)
		for (int i = 0; i < 4; i++)
			v[i][i] = a;
	}
	void init(double a=0) {
		memset(v, 0, sizeof(v));
		if (a != 0)
		for (int i = 0; i < 4; i++)
			v[i][i] = a;
	}
	Matrix operator*(const Matrix &x) const {
		Matrix ret(0);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				double sum = 0;
				for (int k = 0; k < 4; k++)
					sum += v[i][k] * x.v[k][j];
				ret.v[i][j] = sum;
			}
		}
		return ret;
	}
	void print() {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				printf("%lf ", v[i][j]);
			puts("");
		}
	}
};
struct Pt {
	double x, y, z;
	void read() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	Pt(double x=0, double y=0, double z=0):
		x(x), y(y), z(z) {}
	Pt trans(Matrix &t) {
		double tx, ty, tz;
		tx = t.v[0][0]*x+t.v[0][1]*y+t.v[0][2]*z+t.v[0][3];
		ty = t.v[1][0]*x+t.v[1][1]*y+t.v[1][2]*z+t.v[1][3];
		tz = t.v[2][0]*x+t.v[2][1]*y+t.v[2][2]*z+t.v[2][3];
		return Pt(tx, ty, tz);
	}
	static Pt cross(Pt a, Pt b, Pt c) {
		b.x -= a.x, b.y -= a.y, b.z -= a.z;
		c.x -= a.x, c.y -= a.y, c.z -= a.z;
		return Pt(b.y*c.z-b.z*c.y, b.z*c.x-b.x*c.z, b.x*c.y-b.y*c.x);
	}
	void normal() {
		double v = sqrt(x*x+y*y+z*z);
		x /= v, y /= v, z /= v;
	}
	void print() {
		printf("%.2lf %.2lf %.2lf\n", x, y, z);
	}
};
struct Plane {
	// ax + by + cz + d = 0
	double a, b, c, d;
	void read() {
		scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	}
	Plane trans(Matrix &t) {
		Pt pta, ptb, ptc;
		double mx = max(max(fabs(a), fabs(b)), fabs(c));
		if (fabs(a) == mx)
			pta = Pt(-d/a, 0, 0), ptb = Pt((-d-b)/a, 1, 0), ptc = Pt((-d-c)/a, 0, 1);
		else if (fabs(b) == mx)
			pta = Pt(1, (-d-a)/b, 0), ptb = Pt(0, -d/b, 0), ptc = Pt(0, (-d-c)/b, 1);
		else
			pta = Pt(1, 0, (-d-a)/c), ptb = Pt(0, 1, (-d-b)/c), ptc = Pt(0, 0, -d/c);
		pta = pta.trans(t), ptb = ptb.trans(t), ptc = ptc.trans(t);
		Pt v = Pt::cross(pta, ptb, ptc);
		v.normal();
		Plane ret;
		ret.a = v.x, ret.b = v.y, ret.c = v.z, ret.d = -(v.x*pta.x+v.y*pta.y+v.z*pta.z);
		return ret;
	}
	void print() {
		printf("%.2lf %.2lf %.2lf %.2lf\n", a, b, c, d);
	}
};
static const int MAXN = 50005;
static Pt pts[MAXN];
static Plane pls[MAXN];
static Matrix trans;
void translate() {
	static Matrix t(1);
	double a, b, c;
	scanf("%lf%lf%lf", &a, &b, &c);
	t.v[0][3] = a, t.v[1][3] = b, t.v[2][3] = c;
	trans = t * trans;
}
void rotate() {
	static Matrix t(1);
	double a, b, c, d, n;
	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	n = sqrt(a*a+b*b+c*c);
	a /= n, b /= n, c /= n;
	double rad = d*pi/180;
	double ct = cos(rad), st = sin(rad);
	t.v[0][0] = (1-ct)*a*a + ct, t.v[0][1] = (1-ct)*a*b - st*c, t.v[0][2] = (1-ct)*a*c + st*b;
	t.v[1][0] = (1-ct)*b*a + st*c, t.v[1][1] = (1-ct)*b*b + ct, t.v[1][2] = (1-ct)*b*c - st*a;
	t.v[2][0] = (1-ct)*c*a - st*b, t.v[2][1] = (1-ct)*c*b + st*a, t.v[2][2] = (1-ct)*c*c + ct;
	trans = t * trans;
}
void scale() {
	static Matrix t(1);
	double a, b, c;
	scanf("%lf%lf%lf", &a, &b, &c);
	t.v[0][0] = a, t.v[1][1] = b, t.v[2][2] = c;
	trans = t * trans;
}
int main() {
	int n, m, t;
	char cmd[32];
	while (scanf("%d %d %d", &n, &m, &t) == 3) {
		trans.init(1);
		for (int i = 0; i < n; i++)
			pts[i].read();
		for (int i = 0; i < m; i++)
			pls[i].read();
		for (int i = 0; i < t; i++) {
			scanf("%s", cmd);
			if (cmd[0] == 'T')
				translate();
			else if (cmd[0] == 'R')
				rotate();
			else
				scale();
		}
		for (int i = 0; i < n; i++)
			pts[i].trans(trans).print();
		for (int i = 0; i < m; i++)
			pls[i].trans(trans).print();
	}
	return 0;
}
/*
1 2 3
1 2 3
0 0 1 -2
3 4 1 -2
TRANSLATE 2 3 4
ROTATE 1 0 0 90
SCALE 3 2 1

1 2 5
1 2 3
0 0 1 -2
3 4 1 -2
TRANSLATE 2 3 4
ROTATE 1 0 0 90
SCALE 3 2 1
ROTATE 1 4 2 90
TRANSLATE 2 6 4
*/
