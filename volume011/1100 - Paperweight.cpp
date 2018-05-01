#include <bits/stdc++.h>
using namespace std;

const double eps = 1e-6;
const double stable_unit = 0.2;
struct Pt3D {
	double x, y, z;
	int read() {
		return scanf("%lf%lf%lf", &x, &y, &z) == 3;
	}
	Pt3D(double x=0, double y=0, double z=0):
		x(x), y(y), z(z) {}
	static Pt3D cross(Pt3D a, Pt3D b, Pt3D c) {
		b.x -= a.x, b.y -= a.y, b.z -= a.z;
		c.x -= a.x, c.y -= a.y, c.z -= a.z;
		return Pt3D(b.y*c.z-b.z*c.y, b.z*c.x-b.x*c.z, b.x*c.y-b.y*c.x);
	}
	static double dot(Pt3D a, Pt3D b) {
		return a.x*b.x + a.y*b.y + a.z*b.z;
	}
	static double area(Pt3D a, Pt3D b, Pt3D c) {
		return cross(a, b, c).length()/2;
	}
	static double line2pt(Pt3D st, Pt3D ed, Pt3D p) {
		double a = area(st, ed, p);
		return a*2 / st.distance(ed);
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
	double distance(Pt3D p) {
		return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)+(z-p.z)*(z-p.z));
	}
	double length() {
		return sqrt(x*x+y*y+z*z);
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
	Pt3D intersect(Pt3D st, Pt3D ed) {
		Pt3D v = st-ed;
		double t = -(st.x*a+st.y*b+st.z*c+d)/(v.x*a+v.y*b+v.z*c);
		Pt3D o = st + v*t;
		return o;
	}
	Pt3D project(Pt3D p) {
		Pt3D v(a, b, c);
		double t = -(p.x*a+p.y*b+p.z*c+d)/(v.x*a+v.y*b+v.z*c);
		Pt3D o = p + v*t;
		return o;
	}
	double distance(Pt3D p) {
		Pt3D v(a, b, c);
		double t = -(p.x*a+p.y*b+p.z*c+d)/(v.x*a+v.y*b+v.z*c);
		v = v*t;
		return v.length();
	}
	void print() {
		printf("%.2lf %.2lf %.2lf %.2lf\n", a, b, c, d);
	}
};

int cmpZero(double x) {
	if (fabs(x) < eps)
		return 0;
	return x < 0 ? -1 : 1; 
}

double volume(Pt3D a, Pt3D b, Pt3D c, Pt3D d) {
	return fabs(Pt3D::dot(d-a, Pt3D::cross(a, b, c))/6);
}

Pt3D center(Pt3D pt[]) {
	Pt3D c1 = (pt[0]+pt[1]+pt[2]+pt[3])/4;
	Pt3D c2 = (pt[0]+pt[1]+pt[2]+pt[4])/4;
	double v1 = volume(pt[0], pt[1], pt[2], pt[3]);
	double v2 = volume(pt[0], pt[1], pt[2], pt[4]);
	return (c1*v1 + c2*v2)/(v1+v2);
}

pair<bool, vector<Pt3D>> facet(Pt3D a, Pt3D b, Pt3D c, Pt3D pt[], int n) {
	// check the facet(a, b, c) is valid in pt[]
	pair<int, vector<Pt3D>> ret = {false, vector<Pt3D>()};
	Pt3D normal = Pt3D::cross(a, b, c);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		int dir = cmpZero(Pt3D::dot(pt[i]-a, normal));
		if (dir == 0)
			ret.second.push_back(pt[i]);
		else if (dir < 0)
			sum |= 1;
		else if (dir > 0)
			sum |= 2;
		if (sum == 3)
			return ret;
	}
	ret.first = true;
	return ret;
}

int inTriangle(Pt3D a, Pt3D b, Pt3D c, Pt3D p) {
	double t1 = Pt3D::area(p, a, b);
	double t2 = Pt3D::area(p, b, c);
	double t3 = Pt3D::area(p, a, c);
	double t = Pt3D::area(a, b, c);
	return cmpZero(t-t1-t2-t3) == 0;
}

int stable(vector<Pt3D> &pt, Pt3D g) {
	// pt in the same plane
	int n = pt.size();
	int existed = 0;
	// find the point in the triangulation/convex hull in plane
	for (int i = 0; i < n && !existed; i++) {
		for (int j = i+1; j < n && !existed; j++) {
			for (int k = j+1; k < n && !existed; k++) {
				if (inTriangle(pt[i], pt[j], pt[k], g))
					existed = 1;
			}
		}
	}
	if (!existed)
		return 0;
	// find the edge of convex hull
	Pt3D normal = Pt3D::cross(pt[0], pt[1], pt[2]);
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			Pt3D p = pt[i], q = pt[j];
			Pt3D r = Pt3D::cross(normal+p, p, q);
			int sum = 0;
			for (int k = 0; k < n; k++) {
				if (k == i || k == j)
					continue;
				int dir = cmpZero(Pt3D::dot(pt[k]-p, r));
				if (dir < 0)
					sum |= 1;
				else if (dir > 0)
					sum |= 2;
			}
			if (sum == 1 || sum == 2) {
				if (cmpZero(Pt3D::line2pt(p, q, g) - stable_unit) < 0)
					return 0;
			}
		}
	}
	return 1;
}

void paperweight(Pt3D pt[], Pt3D F) {
	Pt3D g = center(pt);
	double mn = 10000, mx = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = i+1; j < 5; j++) {
			for (int k = j+1; k < 5; k++) {
				// find the bottom facet
				auto t = facet(pt[i], pt[j], pt[k], pt, 5);
				if (t.first == false)
					continue;
				Plane bottom = Plane(pt[i], pt[j], pt[k]);
				Pt3D proj_g = bottom.project(g);
				if (!stable(t.second, proj_g))
					continue;
				double dist = bottom.distance(F);
				mn = min(mn, dist), mx = max(mx, dist);
//				printf("%lf\n", dist);
			}
		}
	}
	printf("%.5lf %.5lf\n", mn, mx);
}

int main() {
	int cases = 0;
	Pt3D pts[5], F;
	while (pts[0].read()) {
		for (int i = 1; i < 5; i++)
			pts[i].read();
		F.read();
		printf("Case %d: ", ++cases);
		paperweight(pts, F);
	}
	return 0;
}
/*
0  0  0  
9  0  0  
0  8  0  
0  0  9  
1  1  -8
1  2  -1

0  0  0  7  0  0  0  7  0  0  0  7  -1  -2  -3  2  2  2
1  2  3  6  2  3  -2  6  3  -1  0  7  4  1  -2  -1  5  3
0
*/
