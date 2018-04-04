#include <bits/stdc++.h>
using namespace std;
const int eps = 1e-6;
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):x(a), y(b) {}
    Pt(const Pt &a):x(a.x), y(a.y) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
    double dist2() {
    	return x*x+y*y;
	}
    void print() {
    	printf("%lf %lf\n", x, y);
	}
};
 
struct Seg {
    Pt s, e;
    Seg(Pt s = Pt(0, 0), Pt e = Pt(0, 0)):
		s(s), e(e) {}
    Seg operator-(const Pt &a) const {
    	return Seg(s-a, e-a);
	}
	void print() {
		printf("(%lf %lf) - (%lf %lf)\n", s.x, s.y, e.x, e.y);
	}

};

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
Pt getIntersect(Pt as, Pt ae, Pt bs, Pt be) {
    Pt u = as - bs;
    double t = cross2(be - bs, u)/cross2(ae - as, be - bs);
    return as + (ae - as) * t;
}
int cmpZero(double x) {
    if (fabs(x) < eps)	return 0;
    return x < 0 ? -1 : 1;
}
struct Event {
	Pt pt;
	int type, id;
	Event(Pt pt=Pt(0, 0), int type=0, int id=0):
		pt(pt), type(type), id(id) {}	
	static bool cmp(const Pt& p1, const Pt& p2) {
	    if (p1.y == 0 && p2.y == 0 && p1.x * p2.x <= 0) return p1.x > p2.x;
	    if (p1.y == 0 && p1.x >= 0 && p2.y != 0) return true;
	    if (p2.y == 0 && p2.x >= 0 && p1.y != 0) return false;
	    if (p1.y * p2.y < 0) return p1.y > p2.y;
	    double c = cross2(p1, p2);
	    return c > 0 || (c == 0 && fabs(p1.x) < fabs(p2.x));
	}
	bool operator<(const Event &evt) const {
		return cmp(pt, evt.pt);
	}
};

const int MAXK = 10005;
const int MAXW = 10005;
const int MAXE = MAXK+MAXW*2;
Pt pt[MAXK];
Seg segs[MAXW];
Event evts[MAXE];
struct CMP {
	static Pt base;
	bool operator() (const Seg &a, const Seg &b) {
		Pt v1 = getIntersect(Pt(0, 0), base, a.s, a.e);
        Pt v2 = getIntersect(Pt(0, 0), base, b.s, b.e);
        return cmpZero(v1.dist2() - v2.dist2()) < 0;
	}
};
Pt CMP::base;
set<Seg, CMP> R;
set<Seg, CMP>::iterator Rit[MAXW];
int S, K, W;
int seek(int pid) {
	int e = 0;
	for (int i = 0; i < K; i++) {
		if (i == pid)
			continue;
		evts[e++] = Event(pt[i]-pt[pid], 1, i);
	}
	R.clear();
	CMP::base = Pt(1, 0);
	for (int i = 0; i < W; i++) {
		Seg seg = segs[i] - pt[pid];
		if (cross2(seg.s, seg.e) < 0)
			swap(seg.s, seg.e);
		evts[e++] = Event(seg.s, 0, i);
		evts[e++] = Event(seg.e, -1, i);
		Rit[i] = R.end();
		if (cross2(seg.s, CMP::base) >= 0 && cross2(seg.e, CMP::base) <= 0)
			Rit[i] = R.insert(seg).first;
	}

	int ret = 0, untest = K-1;
	sort(evts, evts+e);
	for (int i = 0; i < e; i++) {
		auto evt = evts[i];
		int id = evt.id, cmd = evt.type;
		CMP::base = evt.pt;
		if (cmd == -1) {
			assert(Rit[id] != R.end() && !R.empty());
			R.erase(Rit[id]);
			Rit[id] = R.end();
		} else if (cmd == 0) {
			assert(Rit[id] == R.end());
			Rit[id] = R.insert(segs[id]-pt[pid]).first;
		} else {
			if (R.empty() || getIntersect(R.begin()->s, R.begin()->e, CMP::base, Pt()).dist2() > evt.pt.dist2())
				ret++;
			untest--;
			if (untest == 0)
				return ret;
		}
	}
	return ret;
}
int main() {
	while (scanf("%d %d %d", &S, &K, &W) == 3) {
		for (int i = 0; i < K; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			pt[i] = Pt(x, y);
		}
		for (int i = 0; i < W; i++) {
			int sx, sy, ex, ey;
			scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
			segs[i] = Seg(Pt(sx, sy), Pt(ex, ey));
		}

		for (int i = 0; i < S; i++) {
			int ret = seek(i);
			printf("%d\n", ret);
		}
	}
	return 0;
}
/*
2 3 2
0 0
100 0
0 100
50 -1 48 3
49 49 51 52

4 4 4
-100 0
0 100
0 -100
100 0
3 3 -2 -2
-101 50 101 50
-101 -101 101 -101
-49 -50 49 -50

5 6 4
40 40
60 10
70 30
60 80
30 81
20 40
0 10 40 50
10 61 30 61
-100 90 200 90
50 20 50 50
*/
