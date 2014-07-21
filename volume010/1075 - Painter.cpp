// Wrong Answer 
#include <stdio.h>
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
#define eps 1e-8
struct Pt {
    double x, y;
	int label;
    Pt(double a = 0, double b = 0, double c = 0):
    	x(a), y(b), label(c) {}
    bool operator<(const Pt &a) const {
        if(x != a.x)	return x < a.x;
        return y < a.y;
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y, label);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y, label);
    }
    Pt operator*(const double v ) const {
        return Pt(x * v, y * v, label);
    }
};

double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs) * cross(as, at, bt) <= 0 &&
       cross(at, as, bs) * cross(at, as, bt) <= 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) <= 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) <= 0)
        return 1;
    return 0;
}

// http://www.csie.ntnu.edu.tw/~u91029/PointLinePlane2.html
struct seg {
	Pt s, e;
	int i;
	seg(Pt a, Pt b, int c):s(a), e(b), i(c) {}
	seg operator*(const double val) {
		seg ret = *this;
		Pt v = (e - s) * val;
		// ret.s = s + ((e - s) - v) * 0.5;
		ret.e = ret.s + v;
		return ret;
	}
};
struct Endpoint {
	int x, s, i;
	Endpoint(int a = 0, int b = 0, int c = 0):
		x(a), s(b), i(c) {}
	bool operator<(const Endpoint &a) const {
		return x < a.x || (x == a.x && s > a.s);
	}
};
struct CMP {
	static double x;
	
	double interpolate(const Pt& p1, const Pt& p2, double& x) {
        if (p1.x == p2.x) return p1.y;
        return p1.y + (double)(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
    }
    
	bool operator()(const seg &i, const seg &j) {
		double a = interpolate(i.s, i.e, x), b = interpolate(j.s, j.e, x);
		return a < b;
	}
};
double CMP::x = 0;

set<seg, CMP>::iterator prevNode(set<seg, CMP>::iterator it, set<seg, CMP>& S) {
	return it == S.begin() ? it : --it;
}
set<seg, CMP>::iterator nextNode(set<seg, CMP>::iterator it, set<seg, CMP>& S) {
	return it == S.end() ? it : ++it;
}

Pt ABC[100005][3];
int father[100005], dp[100005];
double minfather[100005];

void judgeInTriangle(int idx1, int idx2) { // idx1 in idx2 ?
	if(idx1 == idx2)
		return;
	double a = fabs(cross(ABC[idx2][0], ABC[idx2][1], ABC[idx2][2]));
	double b1 = fabs(cross(ABC[idx1][0], ABC[idx2][1], ABC[idx2][2]));
	double b2 = fabs(cross(ABC[idx2][0], ABC[idx1][0], ABC[idx2][2]));
	double b3 = fabs(cross(ABC[idx2][0], ABC[idx2][1], ABC[idx1][0]));
//	printf("%d -> %d %lf\n", idx1, idx2, a);
	if(fabs(a - b1 - b2 - b3) < eps) {
		if(father[idx1] == -1)
			father[idx1] = idx2, minfather[idx1] = a;
		else {
			if(a < minfather[idx1])
				father[idx1] = idx2, minfather[idx1] = a;
		}
	}
}
bool segment_intersect(vector<seg> segs) {
	for(int i = 0; i < segs.size(); i++)
		if(segs[i].e < segs[i].s)
			swap(segs[i].s, segs[i].e);
			
	vector<Endpoint> e;
	set<seg, CMP> S;
	for(int i = 0; i < segs.size(); i++) {
		e.push_back(Endpoint(segs[i].s.x, 1, i));
		e.push_back(Endpoint(segs[i].e.x, -1, i));
	}
	sort(e.begin(), e.end());
	
	for(int i = 0; i < e.size(); i++) {
		CMP::x = e[i].x;
		if(e[i].s == 1) {
			set<seg, CMP>::iterator it, jt;
			it = S.lower_bound(segs[e[i].i]);
			jt = prevNode(it, S);
//			if(it != S.end()) {
//				printf("%lf %lf %lf %lf %d\n", it->s.x, it->s.y, it->e.x, it->e.y, it->i);
//				printf("%lf %lf %lf %lf %d\n", segs[e[i].i].s.x, segs[e[i].i].s.y, segs[e[i].i].e.x, segs[e[i].i].e.y, segs[e[i].i].i);
//				puts("--");
//			}
//			if(jt != S.end()) {
//				printf("%lf %lf %lf %lf %d\n", jt->s.x, jt->s.y, jt->e.x, jt->e.y, jt->i);
//				printf("%lf %lf %lf %lf %d\n", segs[e[i].i].s.x, segs[e[i].i].s.y, segs[e[i].i].e.x, segs[e[i].i].e.y, segs[e[i].i].i);
//				puts("--");
//			}
			if(it != S.end() && intersection(segs[e[i].i].s, segs[e[i].i].e, it->s, it->e))
				return 1;
			if(jt != S.end() && intersection(segs[e[i].i].s, segs[e[i].i].e, jt->s, jt->e))
				return 1;
			/* ----- */
			if(it != S.end()) {
				judgeInTriangle(segs[e[i].i].i, it->i);
				judgeInTriangle(it->i, segs[e[i].i].i);
			}
			if(jt != S.end()) {
				judgeInTriangle(segs[e[i].i].i, jt->i);
				judgeInTriangle(jt->i, segs[e[i].i].i);
			}
			/* ----- */
			S.insert(segs[e[i].i]);
		} else {
			set<seg, CMP>::iterator it, jt, kt;
			it = S.lower_bound(segs[e[i].i]);
			jt = prevNode(it, S);
			kt = nextNode(it, S);
			if(jt != S.end() && kt != S.end() && intersection(kt->s, kt->e, jt->s, jt->e))
				return 1;
			if(jt != S.end() && kt != S.end()) {
				judgeInTriangle(jt->i, kt->i);
				judgeInTriangle(kt->i, jt->i);
			}
			if(it != S.end())
				S.erase(it);
		}
	}
	return 0;
}

int dfs(int n) {
	if(n == -1)	
		return 0;
	if(dp[n] != -1)		
		return dp[n];
	return dp[n] = (dfs(father[n]) + 1);
}
int main() {
	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	
	int n, cases = 0;
	while(scanf("%d", &n) == 1 && n >= 0) {
		
		vector<seg> segs;
		Pt a, b, c;
		const double vvvv = 1 - 1e-6;
		for(int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y, &c.x, &c.y);
			ABC[i][0] = a, ABC[i][1] = b, ABC[i][2] = c;
			segs.push_back(seg(a, b, i) * vvvv);
			segs.push_back(seg(b, c, i) * vvvv);
			segs.push_back(seg(c, a, i) * vvvv);
			father[i] = dp[i] = -1;
//			printf("%lld\n", cross(a, b, c));
		}
		
		int test = segment_intersect(segs);
		
		printf("Case %d: ", ++cases);
		if(test)
			puts("ERROR");
		else {
			int ret = 0;
//			puts("");
			for(int i = 0; i < n; i++) {
//				printf("ff [%d] %d %d\n", i, father[i], dfs(i));
				ret = max(ret, dfs(i));
			}
			printf("%d shades\n", ret + 1);
		}
	}
	return 0;
}
/*
5
632 289 306 80 523 262
214 410 142 29 521 510
837 833 339 913 414 975
598 800 959 382 966 98
423 780 682 319 114 703
3
393 370 441 575 18 201
962 515 198 117 306 228
548 878 524 310 506 641
5
393 370 441 575 18 201
962 515 198 117 306 228
548 878 524 310 506 641
760 282 773 181 487 90
157 19 172 775 160 121
8 
8 3 8 4 7 4 
14 13 -1 9 9 0 
1 8 7 7 4 10 
5 10 11 8 13 12 
9 10 11 10 11 9 
2 7 9 1 10 6 
5 5 5 6 8 6 
9 2 9 5 6 4 
2
0 0 1 0 0 1 
2 0 1 1 1 -1 
-1
*/
