#include <bits/stdc++.h>
using namespace std;
const double pi = acos(-1);
const double eps = 1e-5;
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
    double x, y;
    Pt(double a = 0, double b = 0):
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
struct Pt3D {
	double x, y, z;
	int read() {
		return scanf("%lf%lf%lf", &x, &y, &z) == 3;
	}
	Pt3D(double x=0, double y=0, double z=0):
		x(x), y(y), z(z) {}
	Pt3D trans(Matrix &t) {
		double tx, ty, tz;
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
    Pt3D operator-(const Pt3D &a) const {
        return Pt3D(x - a.x, y - a.y, z - a.z);
    }
    Pt3D operator/(const double val) const {
        return Pt3D(x / val, y / val, z / val);
    }
    Pt3D operator*(const double val) const {
        return Pt3D(x * val, y * val, z * val);
    }
	void print() {
		printf("%.16lf %.16lf %.16lf\n", (double) x, (double) y, (double) z);
	}
};
struct Plane {
	// ax + by + cz + d = 0
	double a, b, c, d;
	void read() {
		scanf("%lf%lf%lf%lf", &a, &b, &c, &d);
	}
	Plane() {
		
	}
	Plane(Pt3D pta, Pt3D ptb, Pt3D ptc) {
		Pt3D v = Pt3D::cross(pta, ptb, ptc);
		a = v.x, b = v.y, c = v.z, d = -(v.x*pta.x+v.y*pta.y+v.z*pta.z);
	}
	Plane trans(Matrix &t) {
		Pt3D pta, ptb, ptc;
		double mx = max(max(fabs(a), fabs(b)), fabs(c));
		if (fabs(a) == mx)
			pta = Pt3D(-d/a, 0, 0), ptb = Pt3D((-d-b)/a, 1, 0), ptc = Pt3D((-d-c)/a, 0, 1);
		else if (fabs(b) == mx)
			pta = Pt3D(1, (-d-a)/b, 0), ptb = Pt3D(0, -d/b, 0), ptc = Pt3D(0, (-d-c)/b, 1);
		else
			pta = Pt3D(1, 0, (-d-a)/c), ptb = Pt3D(0, 1, (-d-b)/c), ptc = Pt3D(0, 0, -d/c);
		pta = pta.trans(t), ptb = ptb.trans(t), ptc = ptc.trans(t);
		Pt3D v = Pt3D::cross(pta, ptb, ptc);
		v.normal();
		Plane ret;
		ret.a = v.x, ret.b = v.y, ret.c = v.z, ret.d = -(v.x*pta.x+v.y*pta.y+v.z*pta.z);
		return ret;
	}
	Pt3D intersect(Pt3D st, Pt3D ed) {
		Pt3D v = st-ed;
		double t = -(st.x*a+st.y*b+st.z*c+d)/(v.x*a+v.y*b+v.z*c);
		Pt3D o = st + v*t;
		return o;
	}
	void print() {
		printf("%.2lf %.2lf %.2lf %.2lf\n", a, b, c, d);
	}
};

Matrix rotate(double d, Pt3D v) {
	static Matrix t(1);
	double a, b, c, n;
	Pt3D nv;
	if (fabs(v.x) > 0 || fabs(v.y) > 0)
		nv = Pt3D::cross(v, Pt3D(0, 0, 1), Pt3D(0, 0, 0));
	else
		nv = Pt3D(0, 0, 1);
	a = nv.x, b = nv.y, c = nv.z;
//	printf("%lf %lf %lf %lf\n", d, v.x, v.y, v.z);
//	printf("%lf %lf %lf --\n", a, b, c);
	n = sqrt(a*a+b*b+c*c);
	a /= n, b /= n, c /= n;
	double rad = d;
	double ct = cos(rad), st = sin(rad);
	t.v[0][0] = (1-ct)*a*a + ct, t.v[0][1] = (1-ct)*a*b - st*c, t.v[0][2] = (1-ct)*a*c + st*b;
	t.v[1][0] = (1-ct)*b*a + st*c, t.v[1][1] = (1-ct)*b*b + ct, t.v[1][2] = (1-ct)*b*c - st*a;
	t.v[2][0] = (1-ct)*c*a - st*b, t.v[2][1] = (1-ct)*c*b + st*a, t.v[2][2] = (1-ct)*c*c + ct;
//	t.print();
	return t;
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
	Pt3D a[3], light, pt;
	int n;
	while (a[0].read()) {
		a[1].read(), a[2].read();
		light.read();

		Plane aplane(a[0], a[1], a[2]);
		Pt3D normal = Pt3D(aplane.a, aplane.b, aplane.c); 
		double theta = atan2(hypot(aplane.a, aplane.b), aplane.c);
		Matrix trans = rotate(theta, normal);
		scanf("%d", &n);
		
		Pt pts[128], ch[128];
		double tz = 0;
		for (int i = 0; i < n; i++) {
			pt.read();
			Pt3D p = aplane.intersect(light, pt);
//			p.print();
			Pt3D q = p.trans(trans);
//			q.print();
			if (i)
				assert(fabs(tz - q.z) < eps);
			tz = q.z;
			pts[i] = Pt(q.x, q.y);
		}
		
		int ch_n = monotone(n, pts, ch);
		double proj = area(ch, ch_n);
		printf("%.2lf\n", proj);
	}
	return 0;
}
/*
0  0  0
0  1  0
1  0  0
0  0  2
8
0  0  1
0  1  1
1  0  1
1  1  1
0  0  0
0  1  0
1  0  0
1  1  0

-1  1   2
 2  0  -3
 5  1  -2
 3  4   5
8
0  0  1
0  1  1
1  0  1
1  1  1
0  0  0
0  1  0
1  0  0
1  1  0

*/
