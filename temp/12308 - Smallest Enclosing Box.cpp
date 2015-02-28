#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <assert.h>
#include <vector>
#include <string.h>
using namespace std;
#define eps 1e-10
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
    Pt operator/(const double a) const {
        return Pt(x / a, y / a);
    }
    bool operator==(const Pt &a) const {
    	return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
    bool operator<(const Pt &a) const {
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	double length() {
		return hypot(x, y);
	}
	void read() {
		scanf("%lf %lf", &x, &y);
	}
};
struct Pt3D {
    double x, y, z;
    Pt3D(double a = 0, double b = 0, double c = 0):
    	x(a), y(b), z(c) {}	
	Pt3D operator-(const Pt3D &a) const {
        return Pt3D(x - a.x, y - a.y, z - a.z);
    }
    Pt3D operator+(const Pt3D &a) const {
        return Pt3D(x + a.x, y + a.y, z + a.z);
    }
    Pt3D operator*(const double a) const {
        return Pt3D(x * a, y * a, z * a);
    }
    bool operator==(const Pt3D &a) const {
    	return fabs(x - a.x) < eps && fabs(y - a.y) < eps && fabs(z - a.z) < eps;
	}
    bool operator<(const Pt3D &a) const {
		if (fabs(x - a.x) > eps)	return x < a.x;
		if (fabs(y - a.y) > eps)	return y < a.y;
		if (fabs(z - a.z) > eps)	return z < a.z;
		return false;
	}
	double dot(Pt3D &a) {
		return x * a.x + y * a.y + z * a.z;
	}
	double length() {
		return sqrt(x * x + y * y + z * z);
	}
	void read() {
		scanf("%lf %lf %lf", &x, &y, &z);
	}
};
const double pi = acos(-1);
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
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
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
struct Seg {
	Pt s, e;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0): s(a), e(b), label(l) {
	}
	bool operator!=(const Seg &other) const {
		return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
	}
};
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
	if (cmpZero(cross(as, at, bs) * cross(as, at, bt)) <= 0 &&
		cmpZero(cross(bs, bt, as) * cross(bs, bt, at)) <= 0)
		return 1;
	return 0;
}
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
double getAngle(Pt va, Pt vb) { // segment, not vector
	return acos(dot(va, vb) / va.length() / vb.length());
}
Pt rotateRadian(Pt a, double radian) {
	double x, y;
	x = a.x * cos(radian) - a.y * sin(radian);
	y = a.x * sin(radian) + a.y * cos(radian);
	return Pt(x, y);
}
int inPolygon(Pt p[], int n, Pt q) {
	int i, j, cnt = 0;
	for(i = 0, j = n-1; i < n; j = i++) {
		if(onSeg(p[i], p[j], q))
			return 1;
		if(p[i].y > q.y != p[j].y > q.y &&
		q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
		cnt++;
	}
	return cnt&1;
}
#define MAXN 128
double randDouble() {
	return (rand() % 32767) / 32767.0;
}
Pt3D rotate3DVec(Pt3D nVec, double dx, double dy, double dz) {
	Pt3D v = nVec;
	// rotate X-axis
	v = Pt3D(v.x, v.y * cos(dx) - v.z * sin(dx), v.y * sin(dx) + v.z * cos(dx));
	// rotate Y-axis
	v = Pt3D(v.x * cos(dy) + v.z * sin(dy), v.y, - v.x * sin(dy) + v.z * cos(dy));
	// rotate Z-axis
	v = Pt3D(v.x * cos(dz) - v.y * sin(dz), v.x * sin(dz) + v.y * cos(dz), v.z);
	return v;
}
int monotone(int n, Pt p[], Pt ch[]) {
	sort(p, p+n);
	int i, m = 0, t;
	for(i = 0; i < n; i++) {
		while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	for(i = n-1, t = m+1; i >= 0; i--) {
		while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
			m--;
		ch[m++] = p[i];
	}
	return m-1;
}
#define INF 1e+30
double smallRect(int n, Pt p[]) {
	int l = 1, r = 1, u = 1;
	double area = INF, per = INF;
	for(int i = 0; i < n; i++) {
		Pt edge = (p[(i+1)%n]-p[i]) / dist(p[(i+1)%n], p[i]);
		while(dot(edge, p[r%n]-p[i]) < dot(edge, p[(r+1)%n]-p[i]))
			r++;
		while(u < r || cross2(edge, p[u%n]-p[i]) < cross2(edge, p[(u+1)%n]-p[i]))
			u++;
		while(l < u || dot(edge, p[l%n]-p[i]) > dot(edge, p[(l+1)%n]-p[i]))
			l++;
		double w = dot(edge, p[r%n]-p[i]) - dot(edge, p[l%n]-p[i]);
		double h = fabs(cross2(p[i]-p[u%n], p[(i+1)%n]-p[u%n]) / dist(p[i], p[(i+1)%n]));
		area = min(area, w * h);
		per = min(per, (w + h)*2);
	}
	return area;
}
double computeMinVolume(Pt3D nVec, Pt3D D[], int N) {
	double mn, mx, height;
	Pt3D pD[MAXN], pVec;
	Pt p2D[MAXN];
	mn = mx = nVec.dot(D[0]);
	for (int i = 0; i < N; i++) { 
		double t = nVec.dot(D[i]);
		mn = min(mn, t), mx = max(mx, t);
	} 
	height = (mx - mn) / nVec.length();

	for (int i = 0; i < N; i++) { // ax + by + cz - mn = 0
		double t = (nVec.dot(D[i]) - mn) 
					/ (nVec.x * nVec.x + nVec.y * nVec.y + nVec.z * nVec.z);
		pD[i] = Pt3D(D[i].x - t * nVec.x, D[i].y - t * nVec.y, D[i].z - t * nVec.z);
	}
	
	double dx, dy, dz, dx2, dy2, dz2;
	dx = 0, dy = 0;
	dz = - acos(nVec.x / sqrt(nVec.x * nVec.x + nVec.y * nVec.y));
	if (nVec.y < 0)		dz = -dz;
	pVec = rotate3DVec(nVec, dx, dy, dz);
	dx2 = 0, dz2 = 0;
	dy2 = - acos(pVec.z / sqrt(pVec.x * pVec.x + pVec.z * pVec.z));
	for (int i = 0; i < N; i++) {
		Pt3D pVec;
		pVec = rotate3DVec(pD[i], dx, dy, dz);
		pVec = rotate3DVec(pVec, dx2, dy2, dz2);
		p2D[i] = Pt(pVec.x, pVec.y);
//		printf("%lf %lf %lf\n", pVec.x, pVec.y, pVec.z);
	}
//	puts("---");
//	vector<double> dist1, dist2;
//	for (int i = 0; i < N; i++) {
//		for (int j = 0; j < N; j++) {
//			dist1.push_back((pD[i] - pD[j]).length());
//			dist2.push_back((p2D[i] - p2D[j]).length());
//		}
//	} 
//	sort(dist1.begin(), dist1.end());
//	sort(dist2.begin(), dist2.end());
//	for (int i = 0; i < dist1.size(); i++) {
//		printf("%lf %lf, %lf %lf %lf\n", dist1[i], dist2[i], nVec.x, nVec.y, nVec.z);
//		printf("%lf\n", height);
//		assert(fabs(dist1[i] - dist2[i]) < eps);
//	}
//	getchar();
	Pt ch[MAXN];
	int M = monotone(N, p2D, ch);
	double area = smallRect(M, ch);
//	printf("%lf %lf = %lf\n", height, area, height * area);
	return height * area;
}
void test(Pt3D v) {
	double dx, dy, dz;
	Pt3D p; 
	dx = 0, dy = 0;
	dz = - acos(v.x / sqrt(v.x * v.x + v.y * v.y));
	if (v.y < 0)	dz = -dz;
	p = rotate3DVec(v, dx, dy, dz);
	dx = 0, dz = 0;
	dy = - acos(p.z / sqrt(p.x * p.x + p.z * p.z));
	p = rotate3DVec(p, dx, dy, dz);
	printf("%lf %lf %lf\n", p.x, p.y, p.z);
	printf("%lf %lf\n", v.length(), p.length());
}
double annealing(Pt3D D[], int N) {
#define S_MUL 0.5f
#define S_LEN acos(-1)
#define T_CNT 20
#define E_CNT 30
	double step = S_LEN; // degree
	Pt3D nVec[E_CNT];
	double val[E_CNT];
	for(int i = 0; i < E_CNT; i++) {
		double x, y, z;
		do {
			x = randDouble() - 0.5;
			y = randDouble() - 0.5;
			z = randDouble() - 0.5;
			if (x || y || z)	break;
		} while (true);
		nVec[i]	= Pt3D(x, y, z);
		val[i] = computeMinVolume(nVec[i], D, N);
	}
	for (int it = 0; it < 20; it++) {
		for(int i = 0; i < E_CNT; i++) {
			for(int j = 0; j < T_CNT; j++) {
				double dx, dy, dz, tmp_val;
				Pt3D rVec;
				dx = randDouble() * 2 * step - step;
				dy = randDouble() * 2 * step - step;
				dz = randDouble() * 2 * step - step;
				rVec = rotate3DVec(nVec[i], dx, dy, dz);
				tmp_val = computeMinVolume(rVec, D, N);
				if (tmp_val < val[i]) {
					val[i] = tmp_val, nVec[i] = rVec;
				}
			}
		}
		step *= S_MUL;
	}
	double ret = val[0];
	for(int i = 0; i < E_CNT; i++) {
		ret = min(ret, val[i]);
	}
	printf("%.2lf\n", ret);
}
int main() {
//	test(Pt3D(1, 2, 3));
//	test(Pt3D(-1, 2, 3));
//	test(Pt3D(1, -2, 3));
//	test(Pt3D(1, 2, -3));
//	test(Pt3D(-1, -2, 3));
//	test(Pt3D(1, -2, -3));
//	test(Pt3D(-1, 2, -3));
//	test(Pt3D(-1, -2, -3));
	int N;
	Pt3D D[MAXN];
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 0; i < N; i++)
			D[i].read();
		annealing(D, N);
	}
	return 0;
}
/*
9
0 0 0
0 2 0
2 0 0
2 2 0
0 0 2
0 2 2
2 0 2
2 2 2
1 1 1
4
0 0 0
1 1 0
1 0 1
0 1 1
5
0 0 0
3 0 1
2 4 3
0 5 7
3 4 9
5
3 2 0
8 9 0
0 9 7
1 9 0
8 6 6
0
*/
