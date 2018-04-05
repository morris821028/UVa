#include <bits/stdc++.h>
using namespace std;
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
    	return x - a.x == 0 && y - a.y == 0;
    }
    bool operator<(const Pt &a) const {
        if (x - a.x)
            return x < a.x;
        if (y - a.y)
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
const int MAXN = 10005;
int32_t project_fast(Seg segs[], int n) {
	int64_t sum_x = 0, sum_y = 0;
	for (int i = 0; i < n; i++) {
		sum_x += max(segs[i].s.x, segs[i].e.x) - min(segs[i].s.x, segs[i].e.x);
		sum_y += max(segs[i].s.y, segs[i].e.y) - min(segs[i].s.y, segs[i].e.y);
	}

	map<int32_t, vector<int>> inc, dec;
	if (sum_x < sum_y) {
		for (int i = 0; i < n; i++) {
			inc[min(segs[i].s.x, segs[i].e.x)].push_back(i);
			dec[max(segs[i].s.x, segs[i].e.x)].push_back(i);
		}
	} else {
		for (int i = 0; i < n; i++) {
			inc[min(segs[i].s.y, segs[i].e.y)].push_back(i);
			dec[max(segs[i].s.y, segs[i].e.y)].push_back(i);
		}
	}

	auto it = inc.begin(), jt = dec.begin();
	list<int> pool;
	static list<int>::iterator pool_it[MAXN];
	int32_t ret = 0;
	while (it != inc.end()) {
		int a = it->first;
		while (jt != dec.end() && jt->first < a) {
			for (auto idx : jt->second)
				pool.erase(pool_it[idx]);
			jt++;
		}
		for (auto idx1 : it->second) {
			for (auto idx2 : pool) {
				if (fastIntersection(segs[idx1], segs[idx2]))
					ret++;
			}
			pool_it[idx1] = pool.insert(pool.begin(), idx1);
		}
		it++;
	}
	return ret;
}
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
		int32_t ret = 0;
//		for (int i = 0; i < n; i++) {
//			for (int j = i+1; j < n; j++)
//				if (fastIntersection(segs[i], segs[j]))
//					ret++;
//		}
		ret = project_fast(segs, n);
		printf("Case #%d: %d\n", ++cases, ret);
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


