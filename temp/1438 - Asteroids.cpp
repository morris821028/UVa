#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;

const double eps = 1e-8;
const int MAXN = 1024;
int cmpZero(double x) {
	if (fabs(x) < eps)	return 0;
	return x < 0 ? -1 : 1;
}
class ConvexHull3D {
public:
	struct Point3D {
		double x, y, z;
		Point3D(double a = 0, double b = 0, double c = 0):
			x(a), y(b), z(c) {}
		Point3D operator+(const Point3D &a) const {
			return Point3D(x + a.x, y + a.y, z + a.z);
		}
		Point3D operator-(const Point3D &a) const {
			return Point3D(x - a.x, y - a.y, z - a.z);
		}
		Point3D operator/(double a) const {
			return Point3D(x/a, y/a, z/a);
		}
		Point3D operator*(double a) const {
			return Point3D(x*a, y*a, z*a);
		}
		bool operator!=(const Point3D &a) const {
			return cmpZero(x - a.x) || cmpZero(y - a.y) || cmpZero(z - a.z);
		}
		Point3D cross(const Point3D &a) const { // outer product
			return Point3D(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x);
		}
		double dot(const Point3D &a) const {
			return x*a.x + y*a.y + z*a.z;
		}
		double length() {
			return sqrt(x*x+y*y+z*z);
		}
		void read() {
			scanf("%lf %lf %lf", &x, &y, &z);
		}
	};
	struct Face {
		int a, b, c; 	// point3d id
		bool flag; 		// on Convex Hull
	};
	
	int n, tri_num;
	Point3D pt[MAXN];
	Face faces[MAXN*8];
	Face* g[MAXN][MAXN];
	
	double tri_area(Point3D a, Point3D b, Point3D c) { 	// value >= 0
		return ((a - c).cross(b - c)).length()/2;
	}
	double volume(Point3D a, Point3D b, Point3D c, Point3D d) { // directed
		return ((b - a).cross(c - a)).dot(d - a)/6;
	}
	double pt2Face(Point3D a, Point3D b, Point3D c, Point3D p) {
		Point3D n = (b - a).cross(c - a);
		Point3D t = p - a;
		double v = n.dot(t) / n.length();
		return fabs(v);
	}
	double ptWithFace(Point3D &p, Face &f) { // 0: p in f, <0, >0: above or below
		Point3D a, b, c;
		a = pt[f.b] - pt[f.a];
		b = pt[f.c] - pt[f.a];
		c = p - pt[f.a];
		return (a.cross(b)).dot(c);
	}
	bool samePlane(Face &s, Face &t) {
		Point3D a, b, c;
		bool ret = true;
		a = pt[s.a], b = pt[s.b], c = pt[s.c];
		ret = cmpZero(volume(a, b, c, pt[t.a])) == 0 &&
				cmpZero(volume(a, b, c, pt[t.b])) == 0 &&
				cmpZero(volume(a, b, c, pt[t.c])) == 0;
		return ret;
	}
	void deal(int a, int b, int p) {
		Face *f = g[a][b];
		if (f->flag) {
			if (cmpZero(ptWithFace(pt[p], *f)) > 0) {
				dfs(p, f);
			} else {
				Face &add = faces[tri_num++];
				add.a = b, add.b = a, add.c = p;
				add.flag = 1;
				g[b][a] = g[a][p] = g[p][b] = &add;
			}
		}
	}
	void dfs(int p, Face *f) {
		f->flag = 0;	// remove this face.
		deal(f->b, f->a, p);
		deal(f->a, f->c, p);
		deal(f->c, f->b, p);
	}
	
	int make() {
		if (n < 4)
			return 0;		
		// find a tetrahedron
		bool ok;
		ok = false;
		for (int i = 1; i < n; i++) {
			if (pt[0] != pt[i]) {
				swap(pt[1], pt[i]);
				ok = true;
				break;
			}
		}
		if (!ok)	return 0;
		ok = false;
		for (int i = 2; i < n; i++) {
			if (cmpZero(tri_area(pt[0], pt[1], pt[i]))) {
				swap(pt[2], pt[i]);
				ok = true;
				break;
			}
		}
		if (!ok)	return 0;
		ok = false;
		for (int i = 3; i < n; i++) {
			if (cmpZero(volume(pt[0], pt[1], pt[2], pt[i]))) {
				swap(pt[3], pt[i]);
				ok = true;
				break;
			}
		}
		if (!ok)	return 0;
		
		tri_num = 0;
		for (int i = 0; i < 4; i++) { // init 4 faces. 
			Face &f = faces[tri_num++];
			f.a = (i+1)%4, f.b = (i+2)%4, f.c = (i+3)%4;
			f.flag = 1;
			if (cmpZero(ptWithFace(pt[i], f)) > 0)
				swap(f.b, f.c);
			g[f.a][f.b] = g[f.b][f.c] = g[f.c][f.a] = &f;
		}
		// add point into convex hull
		for (int i = 4; i < n; i++) {
			for (int j = 0; j < tri_num; j++) {
				if (faces[j].flag && cmpZero(ptWithFace(pt[i], faces[j])) > 0) {
					dfs(i, &faces[j]);
					break;
				}
			}
		}
		// remove unused face, trash g[][]
		int tri_n = 0;
		for (int i = 0; i < tri_num; i++) {
			if (faces[i].flag)
				faces[tri_n++] = faces[i];
		}
		tri_num = tri_n; 
		return 1;
	}
	double area() { // surface
		double ret = 0;
		if (n == 3)
			return tri_area(pt[0], pt[1], pt[2]);
		for (int i = 0; i < tri_num; i++)
			ret += tri_area(pt[faces[i].a], pt[faces[i].b], pt[faces[i].c]);
		return ret;
	}
	double volume() {
		double ret = 0;
		Point3D o(0, 0, 0);
		for (int i = 0; i < tri_num; i++)
			ret += volume(o, pt[faces[i].a], pt[faces[i].b], pt[faces[i].c]);
		return fabs(ret);
	}
	Point3D getCenter() {
		Point3D ret(0, 0, 0), o = pt[faces[0].a], p;
		double sum, v;
		sum = 0;
		for (int i = 0; i < tri_num; i++) {
			v = volume(o, pt[faces[i].a], pt[faces[i].b], pt[faces[i].c]);
			p = (pt[faces[i].a] + pt[faces[i].b] + pt[faces[i].c] + o)/4.0;
			if (cmpZero(v) > 0) {
				p = p * v;
				ret = ret + p, sum += v;
			}
		}
		ret = ret / sum;
		return ret;
	}
	int getFaceCount() {
		int ret = 0;
		for (int i = 0; i < tri_num; i++) {
			int ok = 1;
			for (int j = 0; j < i && ok; j++) {
				if (samePlane(faces[i], faces[j]))
					ok = 0;
			}
			if (ok)
				ret++;
		}
		return ret;
	}
	double getInnerClosestDist(Point3D p) { // p in Conver Hull
		double ret = -1;
		for (int i = 0; i < tri_num; i++) {
			Point3D a, b, c;
			a = pt[faces[i].a], b = pt[faces[i].b], c = pt[faces[i].c];
			
			double t = tri_area(a, b, c);
			double v = fabs(volume(a, b, c, p));
			
			if (ret < 0 || v*3/t < ret)
				ret = v*3/t;
		}
		return ret;
	} 
} A, B;
int main() {
	while (scanf("%d", &A.n) == 1) {
		for (int i = 0; i < A.n; i++)
			A.pt[i].read();
		
		scanf("%d", &B.n);
		for (int i = 0; i < B.n; i++)
			B.pt[i].read();
			
		A.make();
		B.make();
		
		double d1, d2;
		d1 = A.getInnerClosestDist(A.getCenter());
		d2 = B.getInnerClosestDist(B.getCenter());
		printf("%lf\n", d1 + d2);
	}
	return 0;
}
/*
8
0 0 0
0 0 1
0 1 0
0 1 1
1 0 0
1 0 1
1 1 0
1 1 1
5
0 0 5
1 0 6
-1 0 6
0 1 6
0 -1 6
*/
