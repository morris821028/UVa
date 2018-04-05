#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
struct Pt {
	int32_t x, y;
	Pt(int32_t a = 0, int32_t b = 0):x(a), y(b) {}
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
    bool operator<(const Pt &a) const {
        if (fabs(x - a.x) > eps)
            return x < a.x;
        if (fabs(y - a.y) > eps)
            return y < a.y;
        return false;
    }
};

struct Seg {
    Pt s, e;
    Seg(Pt s = Pt(0, 0), Pt e = Pt(0, 0)):
    	s(s), e(e) {}
};

static inline int fastIntersection(Seg &sa, Seg &sb) {
	Pt a = sa.e - sa.s;
	Pt b = sb.s - sb.e;
	Pt c = sa.s - sb.s;
	int64_t alphaX = (int64_t) b.y*c.x - (int64_t) b.x*c.y;
	int64_t Y = (int64_t) a.y*b.x - (int64_t) a.x*b.y;
	if (Y == 0) {						// parallel
		int64_t betaX = (int64_t) a.x*c.y - (int64_t) a.y*c.x;
		if (alphaX != 0 || betaX != 0)	// no-colinear
			return 0;
		if (a.x == 0)
			return max(min(sa.s.y, sa.e.y), min(sb.s.y, sb.e.y)) <= 
				min(max(sa.s.y, sa.e.y), max(sb.s.y, sb.e.y));
		else
			return max(min(sa.s.x, sa.e.x), min(sb.s.x, sb.e.x)) <= 
				min(max(sa.s.x, sa.e.x), max(sb.s.x, sb.e.x));
		return 0;
	}
	if (Y > 0) {
		if (alphaX < 0 || alphaX > Y)
			return 0;
	} else {
		if (alphaX > 0 || alphaX < Y)
			return 0;
	}
	int64_t betaX = (int64_t) a.x*c.y - (int64_t) a.y*c.x;
	if (Y > 0) {
		if (betaX < 0 || betaX > Y)
			return 0;
	} else {
		if (betaX > 0 || betaX < Y)
			return 0;
	}
	return 1;
}
const int MAXN = 65536;
int main() {
	int testcase, cases = 0;
	int n;
	Seg segs[MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int sx, sy, ex, ey;
			scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
			segs[i] = Seg(Pt(sx, sy), Pt(ex, ey));
		}
		int64_t ret = 0;
		for (int i = 0; i < n; i++) {
			for (int j = i+1; j < n; j++)
				if (fastIntersection(segs[i], segs[j]))
					ret++;
		}
//		for (int i = 0; i < n; i++) {
//			for (int j = i+1; j < n; j++) {
////				if (fastIntersection(segs[i], segs[j]) != intersection(segs[i].s, segs[i].e, segs[j].s, segs[j].e)) {
////					printf("%d %d %d %d\n", segs[i].s.x, segs[i].s.y, segs[i].e.x, segs[i].e.y);
////					printf("%d %d %d %d\n", segs[j].s.x, segs[j].s.y, segs[j].e.x, segs[j].e.y);
////					assert(false);
////				}
//			}
//		}
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}

/*

999

2
0 0 0 1
0 1 1 1

2
0 0 0 1
0 1 0 1

6
1 9 7 9
5 2 1 0
1 9 7 9
3 2 9 4
9 8 5 2
3 6 3 1

6
8 2 6 6
8 9 7 9
6 2 5 9
2 4 8 4
3 5 2 0
8 8 0 5

999
2
2 45 47 72
26 13 26 13

2
25 38 33 95
78 95 15 75
*/


