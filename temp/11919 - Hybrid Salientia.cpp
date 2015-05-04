#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <algorithm>
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
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
double getAngle(Pt va, Pt vb) { // segment, not vector
	return acos(dot(va, vb) / va.length() / vb.length());
}	
double distSeg2Point(Pt a, Pt b, Pt p) {
	Pt c, vab;
	vab = a - b;
	if (between(a, b, p)) {
		c = getIntersect(Seg(a, b), Seg(p, Pt(p.x+vab.y, p.y-vab.x)));
		return (p - c).length();
	}
	return min((p - a).length(), (p - b).length());
}
Pt rotateRadian(Pt a, double radian) {
	double x, y;
	x = a.x * cos(radian) - a.y * sin(radian);
	y = a.x * sin(radian) + a.y * cos(radian);
	return Pt(x, y);
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
const double pi = acos(-1);
// this problem
int n;
double dist[16][16], R[16];
Pt XY[16];
char type[16][16];
void placeSquare(Pt LR, double r, Pt A[]) {
	A[0] = LR;
	A[1] = Pt(LR.x, LR.y+r);
	A[2] = Pt(LR.x+r, LR.y+r);
	A[3] = Pt(LR.x+r, LR.y);
}
double calcDistance(int p, int q) {
	if (type[p][0] == 'C' && type[q][0] == 'C') {
		Pt vab = XY[p] - XY[q];
		return vab.length() - R[p] - R[q];
	}
	if (type[p][0] == 'S' && type[q][0] == 'S') {
		double ret = 1e+30;
		Pt a[4], b[4], vab, c;
		placeSquare(XY[p], R[p], a);
		placeSquare(XY[q], R[q], b);
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				ret = min(ret, distSeg2Point(a[i], a[(i+1)%4], b[j]));
				ret = min(ret, distSeg2Point(b[i], b[(i+1)%4], a[j]));
			}
		} 
		return ret;
	}
	double ret = 1e+30, r;
	Pt a[4], b;
	if (type[p][0] == 'S')
		placeSquare(XY[p], R[p], a), b = XY[q], r = R[q];
	else
		placeSquare(XY[q], R[q], a), b = XY[p], r = R[p];
		
	for (int i = 0; i < 4; i++) {
		ret = min(ret, distSeg2Point(a[i], a[(i+1)%4], b) - r);
	}
	return ret;
}
void buildDistance() {
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			dist[i][j] = dist[j][i] = calcDistance(i, j);
		}
		dist[i][i] = 0;
	}
}

double dp[1<<15][15];
int main() {
	const double INF = 1e+30;
	double Pow9[32];
	Pow9[0] = 1;
	for (int i = 1; i < 16; i++)
		Pow9[i] = Pow9[i-1] / 0.9;
	int testcase;
	double x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s %lf %lf %lf", type[i], &x, &y, &R[i]);
			XY[i] = Pt(x, y);
		}
		
		buildDistance();
		
		/*
		for (int i = 0; i < n; i++, puts("")) {
			for (int j = 0; j < n; j++) {
				printf("%lf ", dist[i][j]);
			}
		}
		*/
		
		vector< pair<int, int> > A;
		for (int i = 0; i < (1<<n); i++) {
			A.push_back(make_pair(__builtin_popcount(i), i));
			for (int j = 0; j < n; j++)
				dp[i][j] = INF;
		}
		sort(A.begin(), A.end());
		
		dp[1<<0][0] = 0;
		
		for (int p = 0; p < A.size(); p++) {
			int s = A[p].second, t = A[p].first - 1;
			for (int i = 0; i < n; i++) {
				if (dp[s][i] >= INF)	continue;
				for (int j = 0; j < n; j++) {
					if ((s>>j)&1)
						continue;
					dp[s|(1<<j)][j] = min(dp[s|(1<<j)][j], max(dp[s][i], dist[i][j] * Pow9[t]));
				}
			}
		}
		 
		double ret = INF;
		for (int i = 0; i < n; i++)
			ret = min(ret, dp[(1<<n)-1][i]);
		printf("%.6lf\n", ret);
	}
	return 0;
}
/*
2
2
C 0 0 5
C 10 0 2
3
C 0 0 2
S 10 1 4
S 3 1 2
*/
