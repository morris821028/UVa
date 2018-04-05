#include <bits/stdc++.h>
using namespace std;
const int MAXN = 10005;
struct Pt {
	int32_t x, y;
	Pt(int32_t a = 0, int32_t b = 0):x(a), y(b) {}
	Pt(const Pt &a):x(a.x), y(a.y) {}
    Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
};

struct Seg {
	int32_t x[2], y[2];
    Seg(Pt s = Pt(0, 0), Pt e = Pt(0, 0)) {
		x[0] = s.x, x[1] = e.x;
		y[0] = s.y, y[1] = e.y;
	}
};
bool cmpX(const Seg &a, const Seg &b) {
	return a.x[0] < b.x[0];
}
bool cmpSX(const Seg &a, const Seg &b) {
	return min(a.x[0], a.x[1]) < min(b.x[0], b.x[1]);
}
bool cmpEX(const Seg &a, const Seg &b) {
	return max(a.x[0], a.x[1]) > max(b.x[0], b.x[1]);
}
bool cmpY(const Seg &a, const Seg &b) {
	return a.y[0] < b.y[0];
}
static inline int fastIntersection(const Seg &sa, const Seg &sb) {
	int32_t ax = sa.x[1]-sa.x[0], ay = sa.y[1]-sa.y[0];
	int32_t bx = sb.x[0]-sb.x[1], by = sb.y[0]-sb.y[1];
	int32_t cx = sa.x[0]-sb.x[0], cy = sa.y[0]-sb.y[0];
	int64_t alphaX = (int64_t) by*cx - (int64_t) bx*cy;
	int64_t Y = (int64_t) ay*bx - (int64_t) ax*by;
	if (Y == 0) {						// parallel
		int64_t betaX = (int64_t) ax*cy - (int64_t) ay*cx;
		if (alphaX != 0 || betaX != 0)	// no-colinear
			return 0;
		if (ax == 0)
			return max(min(sa.y[0], sa.y[1]), min(sb.y[0], sb.y[1])) <= 
				min(max(sa.y[0], sa.y[1]), max(sb.y[0], sb.y[1]));
		else
			return max(min(sa.x[0], sa.x[1]), min(sb.x[0], sb.x[1])) <= 
				min(max(sa.x[0], sa.x[1]), max(sb.x[0], sb.x[1]));
		return 0;
	}
	if (Y > 0) {
		if (alphaX < 0 || alphaX > Y)
			return 0;
	} else {
		if (alphaX > 0 || alphaX < Y)
			return 0;
	}
	int64_t betaX = (int64_t) ax*cy - (int64_t) ay*cx;
	if (Y > 0) {
		if (betaX < 0 || betaX > Y)
			return 0;
	} else {
		if (betaX > 0 || betaX < Y)
			return 0;
	}
	return 1;
}
static int ap(Seg segs[], int n) {
	int ret = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++)
			if (fastIntersection(segs[i], segs[j]))
				ret++;
	}
	return ret;
}
static int rbl(Seg segsA[], int nA, Seg segsB[], int nB) {
	if (nA == 0 || nB == 0)
		return 0;
	int ret = 0;
	static int32_t L[MAXN];
	if (nA < nB)
		swap(segsA, segsB), swap(nA, nB);
	sort(segsB, segsB+nB, cmpSX);
	for (int i = 0; i < nB; i++)
		L[i] = min(segsB[i].x[0], segsB[i].x[1]);
	for (int i = 0; i < nA; i++) {
		int lx = max(segsA[i].x[0], segsA[i].x[1]);
		for (int j = 0; j < nB; j++) {
			if (L[j] > lx)
				break;
			if (fastIntersection(segsA[i], segsB[j]))
				ret++;
		}
	}
	return ret;
}
static int rbr(Seg segsA[], int nA, Seg segsB[], int nB) {
	if (nA == 0 || nB == 0)
		return 0;
	int ret = 0;
	static int32_t R[MAXN];
	if (nA < nB)
		swap(segsA, segsB), swap(nA, nB);
	sort(segsB, segsB+nB, cmpEX);
	for (int i = 0; i < nB; i++)
		R[i] = max(segsB[i].x[0], segsB[i].x[1]);
	for (int i = 0; i < nA; i++) {
		int lx = min(segsA[i].x[0], segsA[i].x[1]);
		for (int j = 0; j < nB; j++) {
			if (R[j] < lx)
				break;
			if (fastIntersection(segsA[i], segsB[j]))
				ret++;
		}
	}
	return ret;
}

static inline int dc(Seg segs[], int n) {
	if (n < 64)
		return ap(segs, n);
	int64_t sum_x = 0, sum_y = 0;
	for (int i = 0; i < n; i++) {
		sum_x += abs(segs[i].x[0] - segs[i].x[1]);
		sum_y += abs(segs[i].y[0] - segs[i].y[1]);
	}
	const int m = n/2;
	Seg *L = NULL, *M = NULL, *R = NULL;
	int Lsize = 0, Msize = 0, Rsize = 0;
	if (sum_x < sum_y) {
		nth_element(segs, segs+m, segs+n, cmpX);
		const int mval = (segs[m].x[0] + segs[m].x[1])/2;
		L = segs;
		R = std::partition(segs, segs+n, [mval](const Seg &s) {
			int r = max(s.x[0], s.x[1]);
			return r < mval;
		});
		M = std::partition(R, segs+n, [mval](const Seg &s) {
			int l = min(s.x[0], s.x[1]);
			return l > mval;
		});
		Msize = segs+n - M;
		Rsize = M - R;
		Lsize = R - segs;
	} else {
		nth_element(segs, segs+m, segs+n, cmpY);
		const int mval = (segs[m].y[0] + segs[m].y[1])/2;
		L = segs;
		R = std::partition(segs, segs+n, [mval](const Seg &s) {
			int r = max(s.y[0], s.y[1]);
			return r < mval;
		});
		M = std::partition(R, segs+n, [mval](const Seg &s) {
			int l = min(s.y[0], s.y[1]);
			return l > mval;
		});
		Msize = segs+n - M;
		Rsize = M - R;
		Lsize = R - segs;
	}
	int ret = 0;
	if (Lsize == 0 && Rsize == 0) {
        ret += ap(M, Msize);
	} else {
		ret += rbl(L, Lsize, M, Msize);
		ret += rbr(R, Rsize, M, Msize);
		ret += dc(M, Msize);
		ret += dc(L, Lsize);
		ret += dc(R, Rsize);
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
		ret = dc(segs, n);
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


