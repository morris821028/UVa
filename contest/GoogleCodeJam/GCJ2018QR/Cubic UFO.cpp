#include <bits/stdc++.h>
using namespace std;
#define eps 1e-16
struct Pt {
    long double x, y;
    Pt(long double a = 0, long double b = 0):
    x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if (fabs(x-a.x) > eps)	return x < a.x;
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
struct Matrix {
	long double v[4][4];
	Matrix(long double a=0) {
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
struct Pt3D {
	long double x, y, z;
	void read() {
		scanf("%lf%lf%lf", &x, &y, &z);
	}
	Pt3D(double x=0, double y=0, double z=0):
		x(x), y(y), z(z) {}
	Pt3D trans(Matrix &t) {
		long double tx, ty, tz;
		tx = t.v[0][0]*x+t.v[0][1]*y+t.v[0][2]*z+t.v[0][3];
		ty = t.v[1][0]*x+t.v[1][1]*y+t.v[1][2]*z+t.v[1][3];
		tz = t.v[2][0]*x+t.v[2][1]*y+t.v[2][2]*z+t.v[2][3];
		return Pt3D(tx, ty, tz);
	}
	static Pt3D cross(Pt3D a, Pt3D b, Pt3D c) {
		b.x -= a.x, b.y -= a.y, b.z -= a.z;
		c.x -= a.x, c.y -= a.y, c.z -= a.z;
		return Pt3D(b.y*c.z-b.z*c.y, b.z*c.x-b.x*c.z, b.x*c.y-b.y*c.x);
	}
	void normal() {
		double v = sqrt(x*x+y*y+z*z);
		x /= v, y /= v, z /= v;
	}
	Pt3D operator+(const Pt3D &a) const {
        return Pt3D(x + a.x, y + a.y, z + a.z);
    }
    Pt3D operator/(const double val) const {
        return Pt3D(x / val, y / val, z / val);
    }
	void print() {
		printf("%.16lf %.16lf %.16lf\n", (double) x, (double) y, (double) z);
	}
};
static Matrix trans;
const double pi = acos(-1);
void rotate(long double d) {
	static Matrix t(1);
	long double a, b, c, n;
	a = 1, c = -1, b = 0;
//	scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	n = sqrt(a*a+b*b+c*c);
	a /= n, b /= n, c /= n;
	long double rad = d;
	long double ct = cos(rad), st = sin(rad);
	t.v[0][0] = (1-ct)*a*a + ct, t.v[0][1] = (1-ct)*a*b - st*c, t.v[0][2] = (1-ct)*a*c + st*b;
	t.v[1][0] = (1-ct)*b*a + st*c, t.v[1][1] = (1-ct)*b*b + ct, t.v[1][2] = (1-ct)*b*c - st*a;
	t.v[2][0] = (1-ct)*c*a - st*b, t.v[2][1] = (1-ct)*c*b + st*a, t.v[2][2] = (1-ct)*c*c + ct;
	trans = t;
}

double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for (i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) < 0)
            m--;
        ch[m++] = p[i];
    }
    for (i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) < 0)
            m--;
        ch[m++] = p[i];
    }
    return m-1;
}
double area(Pt p[], int n) {
    if(n < 3)   return 0.f;
    double ret = 0;
    p[n] = p[0];
    for (int i = 0; i < n; i++)
		ret += p[i].x*p[i+1].y-p[i].y*p[i+1].x;
    return fabs(ret)/2;
}
int main() {
	Pt3D pts[8] = {Pt3D(0.5, 0.5, 0.5), Pt3D(0.5, 0.5, -0.5), 
				Pt3D(0.5, -0.5, 0.5), Pt3D(0.5, -0.5, -0.5), 
				Pt3D(-0.5, 0.5, 0.5), Pt3D(-0.5, 0.5, -0.5), 
				Pt3D(-0.5, -0.5, 0.5), Pt3D(-0.5, -0.5, -0.5)};
	const double RLIMIT = atan2(sqrt(2), 1);
	const double MAXA = sqrt(3);
	int testcase, cases = 0;
	double A;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf", &A);
		long double l = 0, r = RLIMIT, m;
		for (int it = 0; it < 1000; it++) {
			m = (l+r)/2;
			rotate(m);
			Pt p[16], ch[16];
			for (int i = 0; i < 8; i++) {
				Pt3D t = pts[i].trans(trans);
				p[i] = Pt(t.x, t.z);
			}
			int ch_n = monotone(8, p, ch);
			double a = area(ch, ch_n);
			if (a > A)
				r = m;
			else
				l = m;
		}
		Pt3D pt[8];
		for (int i = 0; i < 8; i++)
			pt[i] = pts[i].trans(trans);
		printf("Case #%d:\n", ++cases);
		Pt3D c;
		c = (pt[0] + pt[1] + pt[2] + pt[3])/4;
		c.print();

		c = (pt[0] + pt[1] + pt[4] + pt[5])/4;
		c.print();
		
		c = (pt[0] + pt[2] + pt[4] + pt[6])/4;
		c.print();
	}
	return 0;
}
/*
3
1.000000
1.414213
1.732050
*/
