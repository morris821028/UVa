#include <bits/stdc++.h>
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
double dist(Pt a, Pt b) {
	return hypot(a.x-b.x, a.y-b.y);
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
    if (cmpZero(cross(as, at, bs) * cross(as, at, bt)) < 0 &&
        cmpZero(cross(bs, bt, as) * cross(bs, bt, at)) < 0)
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

int main() {
	int n, cases = 0;
	const int MAXN = 128;
	Seg segs[MAXN];
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) {
			Pt st, ed;
			st.read(), ed.read();
			segs[i] = Seg(st, ed, i);
		}
		
		int ret = 0;
		for (int i = 0; i < n; i++) {
			set<Pt> S;
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				if (intersection(segs[i].s, segs[i].e, segs[j].s, segs[j].e)) {
					Pt x = getIntersect(segs[i], segs[j]);
					S.insert(x);
				}
			}
			
			vector<double> d;
			for (auto e: S)
				d.push_back(dist(e, segs[i].s));
			sort(d.begin(), d.end());
			
			double len = dist(segs[i].s, segs[i].e);
			for (int i = 0; i < d.size(); i++) {
//				printf("%lf ", d[i]);
				if (i == 0) {
					if (d[i] >= 25 - eps)
						ret += floor((d[i]-25)/50+eps)+1;
				}
				
				if (i == d.size()-1) {
					if (len - d[i] >= 25 - eps)
						ret += floor((len-d[i]-25)/50+eps)+1;
				}
				
				if (i > 0) {
					double dd = d[i]-d[i-1];
					ret += floor(dd/50 + eps);
				}
			}
			
			if (d.size() == 0)
				ret += floor(len/50 + eps)+1;
//			printf("\n");
		}
		printf("Map %d\n", ++cases);
		printf("Trees = %d\n", ret);
	}
	return 0;
}
/*
3
0  40  200  40
40  0  40  200
0  200  200  0
4
0  30  230  30
0  200  230  200
30  0  30  230
200  0  200  230
3
0  1  121  1
0  0  121  4
0  4  121  0
2
0  40  200  40
0  40    0  50
2
0  40  200  40
0  40    0  90
0
*/
