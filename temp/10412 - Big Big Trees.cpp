#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <string.h>
#include <assert.h>
#include <vector>
using namespace std;
#define eps 1e-8
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
	double angle;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0):s(a), e(b), label(l) {
//		angle = atan2(e.y - s.y, e.x - s.x);
	}
	bool operator<(const Seg &other) const {
		if (fabs(angle - other.angle) > eps)
			return angle > other.angle;
		if (cross(other.s, other.e, s) > -eps)
			return true;
		return false;
	}
	bool operator!=(const Seg &other) const {
		return !((s == other.s && e == other.e) || (e == other.s && s == other.e));
	}
};
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
	if (as == at && bs == bt)
		return as == bs;
	if (as == at)
		return onSeg(bs, bt, as);
	if (bs == bt)
		return onSeg(as, at, bs);
	if(cross(as, at, bs) * cross(as, at, bt) <= 0 &&
		cross(at, as, bs) * cross(at, as, bt) <= 0 &&
		cross(bs, bt, as) * cross(bs, bt, at) <= 0 &&
		cross(bt, bs, as) * cross(bt, bs, at) <= 0)
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
const double pi = acos(-1);
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}

const int MAXN = 1024;
int HN[MAXN], H[MAXN][32];
int main() {
	int testcase, N, M, K;
	
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &N, &M, &K);
		for (int i = 0; i < N; i++) {
			scanf("%d", &HN[i]);
			for (int j = 0; j < HN[i]; j++)
				scanf("%d", &H[i][j]);
		}
		int dp[MAXN];
		
		memset(dp, 63, sizeof(dp));
		dp[0] = 0;
		
		for (int i = 0; i+1 < N; i++) {
//			printf("%d\n", dp[i]);
			for (int j = 0; j < HN[i]; j++) {
				for (int k = 0; k < HN[i+1]; k++) {
					int dx, dy;
					dx = M - H[i][j] - H[i+1][k];
					dy = abs(j - k);
					if (dx * dx + dy * dy > K * K)
						continue;	
//					printf("%d %d, %d %d\n", j, k, dx, dy);
					int ok = 1;
					for (int p = 0; p < HN[i]; p++) {
						if (p == j)	continue;
						if (intersection(Pt(H[i][j], j), Pt(M-H[i+1][k], k), Pt(0, p), Pt(H[i][p], p)))
							ok = 0;
					}
					for (int p = 0; p < HN[i+1]; p++) {
						if (p == k)	continue;
						if (intersection(Pt(H[i][j], j), Pt(M-H[i+1][k], k), Pt(M, p), Pt(M-H[i+1][p], p)))
							ok = 0;
					}
					if (ok) {
//						printf("--- %d %d %d\n", j, k, H[i][j], H[i+1][k]);
						dp[i+1] = min(dp[i+1], dp[i] + H[i][j] + H[i+1][k]);
					}
				}	
			}
			dp[i+1] = min(dp[i+1], dp[i] + M); // WTF !!!!!!!!!!!!!!! 
		}
		
		printf("%d\n", dp[N-1]);
	}
	return 0;
}
/*
1

5 10 12
1 2
3 2 1 4
8 2 4 4 1 4 0 0 0
8 1 1 2 0 4 1 3 3
10 1 4 0 1 1 1 1 2 1 4


999

5 10 3
2 0 2
1 1
10 1 2 0 1 2 2 0 4 4 4
9 3 1 2 1 2 1 4 1 3
8 0 1 2 1 3 1 0 0

2

2 7 3
4 3 2 2 0
5 3 0 1 0 0

3 50 40
4 15 3 16 10
8 12 12 12 21 12 15 6 14
13 15 23 20 18 14 1 21 9 9 18 23 10 4

999

3 5 100
3 0 0 1
2 0 0
3 0 0 1

2 7 5
1 3
4 3 3 2 1

2 10 2
1 4
2 0 4

2 10 4
1 4
2 0 4

2 10 2
2 0 4
2 0 4
*/
