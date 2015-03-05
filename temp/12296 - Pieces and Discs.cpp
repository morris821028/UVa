#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <assert.h>
#include <vector>
#include <string.h>
using namespace std;
#define eps 1e-6
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
    bool operator==(const Pt &a) const {
    	return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
	bool operator!=(const Pt &a) const {
    	return !(a == *this);
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
int inPolygon(vector<Pt> &p, Pt q) {
	int i, j, cnt = 0;
	int n = p.size();
	for(i = 0, j = n-1; i < n; j = i++) {
		if(onSeg(p[i], p[j], q))
			return 1;
		if(p[i].y > q.y != p[j].y > q.y &&
		q.x < (p[j].x-p[i].x)*(q.y-p[i].y)/(p[j].y-p[i].y) + p[i].x)
		cnt++;
	}
	return cnt&1;
}
// this problem, convex polygon, circle intersection.
double polygonArea(vector<Pt> &p) {
    double area = 0;
    int n = p.size();
    for(int i = 0; i < n;i++)
		area += p[i].x * p[(i+1)%n].y - p[i].y * p[(i+1)%n].x;
    return fabs(area) /2;
}
vector< vector<Pt> > splitPolygon(Pt st, Pt ed, vector< vector<Pt> > pieces) {
	vector< vector<Pt> > ret;
	for (int i = 0; i < pieces.size(); i++) {
		int d = 0, ok = 1;
		for (int j = 0; j < pieces[i].size(); j++) {
			int t = cmpZero(cross(st, ed, pieces[i][j]));
			if (d == 0 && t)		d = t;
			if (d && t && d != t)	ok = 0;
		}
		if (ok) {
			ret.push_back(pieces[i]);
		} else {
			vector<Pt> A, B;
			int in = 0, icnt = 0;
			Pt inp[2];
			for (int j = 0, k = pieces[i].size() - 1; j < pieces[i].size(); k = j++) {
				if (in == 0) {
					if (A.size() == 0 || A.back() != pieces[i][k])
						A.push_back(pieces[i][k]);
				} else {
					if (B.size() == 0 || B.back() != pieces[i][k])
						B.push_back(pieces[i][k]);
				}
				if (intersection(st, ed, pieces[i][k], pieces[i][j])) {
					Pt p = getIntersect(Seg(st, ed), Seg(pieces[i][k], pieces[i][j]));
					if (icnt && inp[icnt-1] == p)
						continue;
					if (A.size() == 0 || A.back() != p)
						A.push_back(p);
					if (B.size() == 0 || B.back() != p)
						B.push_back(p);
					inp[icnt++] = p;
					in = !in;
				}
			}
			if (A.size() >= 2 && A.front() == A.back())
				A.pop_back();
			if (B.size() >= 2 && B.front() == B.back())
				B.pop_back();
			ret.push_back(A);
			ret.push_back(B);
		}
	}
	return ret;
}
Pt projectLine(Pt as, Pt ae, Pt p) {
	double a, b, c, v;
	a = as.y - ae.y, b = ae.x - as.x;
	c = - (a * as.x + b * as.y);
	v = a * p.x + b * p.y + c;
	return Pt(p.x - v*a / (a*a+b*b), p.y - v*b/ (a*a+b*b));
}
int main() {
	int n, m;
	double L, W;
	while (scanf("%d %d %lf %lf", &n, &m, &L, &W) == 4) {
		if (n == 0 && m == 0)
			break;
		vector< vector<Pt> > pieces;
		vector<Pt> rect;
		rect.push_back(Pt(0, 0));
		rect.push_back(Pt(L, 0));
		rect.push_back(Pt(L, W));
		rect.push_back(Pt(0, W));
		pieces.push_back(rect);
		for (int i = 0; i < n; i++) {
			Pt st, ed;
			st.read(), ed.read();
			pieces = splitPolygon(st, ed, pieces);
			double sum = 0;
			for (int i = 0; i < pieces.size(); i++) {
//				for (int j = 0; j < pieces[i].size(); j++)
//					printf("(%.2lf, %.2lf) ", pieces[i][j].x, pieces[i][j].y);
//				puts("--");
				sum += polygonArea(pieces[i]);
			}
			assert(cmpZero(sum - L * W) == 0);
		}
		for (int i = 0; i < m; i++) {
			double x, y, r;
			scanf("%lf %lf %lf", &x, &y, &r);
			
			vector<double> area;
			for (int j = 0; j < pieces.size(); j++) {
				int f = 0;
				for (int k = 0, l = pieces[j].size() - 1; k < pieces[j].size() && !f; l = k++) {
					double dist = (pieces[j][k] - Pt(x, y)).length();
					if (dist < r - eps)
						f = 1;
					Pt p = projectLine(pieces[j][k], pieces[j][l], Pt(x, y));
					if (between(pieces[j][k], pieces[j][l], Pt(x, y)) 
						&& (p - Pt(x, y)).length() < r - eps)
						f = 1;
					if (((pieces[j][k] + pieces[j][l]) * 0.5 - Pt(x, y)).length() < r - eps)
						f = 1;
				}
				if (!f)
					f |= inPolygon(pieces[j], Pt(x, y));
				if (f)
					area.push_back(polygonArea(pieces[j]));
			}
			sort(area.begin(), area.end());
			printf("%d", area.size());
			for (int j = 0; j < area.size(); j++)
				printf(" %.2lf", area[j]);
			puts("");
		}
		puts("");
	}
	return 0;
}
/*
2 2 10 10
0 4 10 4
4 0 4 10
2 4 2
4 4 1

2 1 10 10
0 0 10 10
10 0 0 10
1 1 1

4 2 10 10
0 4 10 4
1 0 7 10
5 10 10 1
2 10 6 0
3 7 3
5 5 5

3 3 10 10
0 4 10 4
1 0 7 10
5 10 10 1
6 3 2
5 4 1
7 2 2

3 3 10 10
0 4 10 4
1 0 7 10
4 10 10 1
6 3 2
5 4 1
7 2 2

1 1 10 10
0 0 10 0
5 5 5

3 2 10 10
0 4 10 4
2 10 10 2
0 2 8 10
5 4 3
4 5 1

4 1 10 10
0 3 10 7
0 7 10 3
3 10 7 0
3 0 7 10
5 2 1

0 0 0 0 
*/
