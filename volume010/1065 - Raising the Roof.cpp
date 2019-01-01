#include <bits/stdc++.h> 
using namespace std;
const double eps = 1e-8;

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

int cmpZero(double x) {
	if (fabs(x) < eps)
		return 0;
	return x < 0 ? -1 : 1; 
}

const int MAXN = 310;
const int MAXT = 1010;
Pt3D p[MAXT];
int tri[MAXT][3];

struct Event {
	double y;
	int id;
	Event(double y, int id): y(y), id(id) {}
	bool operator<(const Event& e) const {
		return y < e.y;
	}
};

double aerial_view(int n, int m) {
	static Pt3D normal[MAXT];
	static double d[MAXT]; 			// E: ax + by + cz = d
	static double area_ratio[MAXT]; // project to x-y plane
	for (int i = 0; i < m; i++) {
		Pt3D a = p[tri[i][0]], b = p[tri[i][1]], c = p[tri[i][2]];
		normal[i] = Pt3D::cross(a, c, b);
		d[i] = Pt3D::dot(normal[i], a);
		if (cmpZero(normal[i].z) != 0)
			area_ratio[i] = fabs(normal[i].length() / normal[i].z);
	}

	// sweeping
	vector<double> X;
	for (int i = 1; i <= n; i++)
		X.push_back(p[i].x);
	for (int i = 0; i < m; i++) { for (int j = i+1; j < m; j++) {
		for (int a = 0; a < 3; a++) { for (int b = 0; b < 3; b++) {
			Pt3D pa = p[tri[i][a]];
			Pt3D pb = p[tri[i][(a+1)%3]];
			Pt3D pab = pb - pa;

			Pt3D qa = p[tri[j][b]];
			Pt3D qb = p[tri[j][(b+1)%3]];
			Pt3D qab = qb - qa;

			double d = pab.x * qab.y - pab.y * qab.x;
			if (cmpZero(d) == 0)
				continue;
			double t = (qab.y*(qa.x - pa.x)+qab.x*(pa.y - qa.y)) / d;
			double s = (pab.y*(qa.x - pa.x)+pab.x*(pa.y - qa.y)) / d;
			if (t < 0 || t > 1 || s < 0 || s > 1)
				continue;
			X.push_back(pa.x + pab.x*t);
	} } } }

	sort(X.begin(), X.end());
	X.erase(unique(X.begin(), X.end()), X.end());

	double ret = 0;
	for (int i = 1; i < X.size(); i++) {
		double lX = X[i-1], rX = X[i];
		double midX = (lX + rX)/2;
		vector<Event> evts;
		for (int j = 0; j < m; j++) {
			if (cmpZero(normal[j].z) == 0)
				continue;
			for (int a = 0; a < 3; a++) {
				Pt3D pa = p[tri[j][a]];
				Pt3D pb = p[tri[j][(a+1)%3]];
				if (cmpZero(pa.x - pb.x) == 0)
					continue;
				if (min(pa.x, pb.x) <= lX && max(pa.x, pb.x) >= rX) {
					double y = pa.y + (pb.y - pa.y) * (midX - pa.x) / (pb.x - pa.x);
					evts.push_back(Event(y, j));
				}
			}
		}

		if (evts.size() == 0)
			continue;

		int deg[MAXT] = {};
		sort(evts.begin(), evts.end());
		for (int j = 0; j < evts.size()-1; j++) {
			deg[evts[j].id] ^= 1;
			if (cmpZero(evts[j].y - evts[j+1].y) == 0)
				continue;
			double project_area = (rX - lX) * (evts[j+1].y - evts[j].y);
			int top = -1;
			double topZ = -1e9;
			double midY = (evts[j].y + evts[j+1].y)/2;
			for (int k = 0; k < m; k++) {
				if (deg[k]) {
					double z = (d[k] - normal[k].x*midX - normal[k].y*midY) / normal[k].z;
					if (z > topZ)
						topZ = z, top = k;
				}
			}
			if (top >= 0)
				ret += project_area * area_ratio[top];
		}
	}	
	return ret;
}

int main() {
	int n, m;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n > 0) {
		for (int i = 1; i <= n; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			p[i] = Pt3D(x, y, z);
		}
		for (int i = 0; i < m; i++)
			scanf("%d %d %d", &tri[i][0], &tri[i][1], &tri[i][2]);
		double ret = aerial_view(n, m);
		printf("Case %d: %.2lf\n\n", ++cases, ret);
	}
	return 0;
}
/*
6  2
10  10  10
10  20  10
20  10  10
10  10  20
10  20  20
20  20  20
1  2  3
4  5  6

3 1
10  10 10
10  18  16
20  10  10
1  2  3

0 0
*/
