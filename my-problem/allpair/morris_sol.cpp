#include <stdio.h>
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map> 
#include <functional>
#include <assert.h>
using namespace std;
#define eps 1e-6
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x - a.x) > eps)	return x < a.x;
        if(fabs(y - a.y) > eps)	return y < a.y;
        return false;
    }
    bool operator>(const Pt &a) const {
        if(fabs(x - a.x) > eps)	return x > a.x;
        if(fabs(y - a.y) > eps)	return y > a.y;
        return false;
    }
    bool operator!=(const Pt &a) const {
        return fabs(x - a.x) > eps || fabs(y - a.y) > eps;
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    void print() const {
    	double px = x, py = y;
    	if (fabs(x) < eps)	px = 0;
    	if (fabs(y) < eps)	py = 0;
    	printf("%.6lf %.6lf\n", px, py);
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(Pt a, Pt b, Pt c) {
	return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int intersection(Pt as, Pt at, Pt bs, Pt bt) {
    if(cross(as, at, bs) * cross(as, at, bt) <= 0 &&
       cross(at, as, bs) * cross(at, as, bt) <= 0 &&
       cross(bs, bt, as) * cross(bs, bt, at) <= 0 &&
       cross(bt, bs, as) * cross(bt, bs, at) <= 0)
        return 1;
    return 0;
}
Pt intersectionPt(Pt as, Pt at, Pt bs, Pt bt) {
	double a1, a2, b1, b2, c1, c2, dx, dy, d;
	a1 = as.y - at.y, b1 = -(as.x - at.x), c1 = as.x * a1 + as.y * b1;
	a2 = bs.y - bt.y, b2 = -(bs.x - bt.x), c2 = bs.x * a2 + bs.y * b2;
	dx = c1 * b2 - c2 * b1;
	dy = a1 * c2 - a2 * c1;
	d = a1 * b2 - a2 * b1;
    return Pt(dx/d, dy/d);
}

// http://www.csie.ntnu.edu.tw/~u91029/PointLinePlane2.html
struct seg {
	Pt s, e;
	seg(Pt a, Pt b):s(a), e(b) {}
	bool operator<(const seg &a) const {
        if (s != a.s)	return s < a.s;
        return e < a.e;
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
		return interpolate(i.s, i.e, x) < interpolate(j.s, j.e, x);
	}
};
double CMP::x = 0;

set<seg, CMP>::iterator prevNode(set<seg, CMP>::iterator it, set<seg, CMP>& S) {
	return it == S.begin() ? it : --it;
}
set<seg, CMP>::iterator nextNode(set<seg, CMP>::iterator it, set<seg, CMP>& S) {
	return it == S.end() ? it : ++it;
}
vector<Pt> segment_intersect(vector<seg> segs) {
	for(int i = 0; i < segs.size(); i++)
		if(segs[i].e < segs[i].s)
			swap(segs[i].s, segs[i].e);
			
	vector<Pt> ret;
	vector<Endpoint> e;
	set<seg, CMP> S;
	set<Pt> ret_set;
	priority_queue<Pt, vector<Pt>, greater<Pt> > pQ; // min-heap
	map<Pt, set<seg> > R;
	for(int i = 0; i < segs.size(); i++) {
		e.push_back(Endpoint(segs[i].s.x, 1, i));
		e.push_back(Endpoint(segs[i].e.x, -1, i));
	}
	sort(e.begin(), e.end());
	
	for(int i = 0; i < e.size(); i++) {
		while (!pQ.empty() && pQ.top().x < e[i].x) {
			double now_x = pQ.top().x, next_x;
			set<seg> ins;
			while (!pQ.empty() && fabs(pQ.top().x - now_x) < eps) {
				Pt t = pQ.top();
				pQ.pop();
				set<seg> &v = R[t];
				for (set<seg>::iterator qt = v.begin();
					qt != v.end(); qt++) {
					seg tmp = *qt;
					set<seg, CMP>::iterator it, jt, kt;
					it = S.lower_bound(tmp);
					jt = prevNode(it, S);
					kt = nextNode(it, S);
					if(jt != S.end() && kt != S.end() && intersection(kt->s, kt->e, jt->s, jt->e)) {
						Pt r = intersectionPt(kt->s, kt->e, jt->s, jt->e);
						if (ret_set.find(r) == ret_set.end())
							ret.push_back(r), ret_set.insert(r), pQ.push(r);
						R[r].insert(*kt);
						R[r].insert(*jt);
					}
					if(it != S.end())
						S.erase(tmp);
					if (t != qt->e)
						ins.insert(tmp);
				}
			}
			next_x = e[i].x;
			if (!pQ.empty())
				next_x = min(next_x, pQ.top().x);
			CMP::x = now_x + eps/2;
			for (set<seg>::iterator qt = ins.begin();
				qt != ins.end(); qt++) {
				set<seg, CMP>::iterator it, jt;
				seg t = *qt;
				it = S.lower_bound(t);
				jt = prevNode(it, S);
				if(it != S.end() && intersection(t.s, t.e, it->s, it->e)) {
					Pt r = intersectionPt(t.s, t.e, it->s, it->e);
					if (ret_set.find(r) == ret_set.end())
						ret.push_back(r), ret_set.insert(r), pQ.push(r);
					R[r].insert(t);
					R[r].insert(*it);
				}
				if(jt != S.end() && intersection(t.s, t.e, jt->s, jt->e)) {
					Pt r = intersectionPt(t.s, t.e, jt->s, jt->e);
					if (ret_set.find(r) == ret_set.end())
						ret.push_back(r), ret_set.insert(r), pQ.push(r);
					R[r].insert(t);
					R[r].insert(*jt);
				}
				S.insert(t);
			}
		}
		
		CMP::x = e[i].x;
		if(e[i].s == 1) {
			set<seg, CMP>::iterator it, jt;
			seg t = segs[e[i].i];
			it = S.lower_bound(t);
			jt = prevNode(it, S);
			if(it != S.end() && intersection(t.s, t.e, it->s, it->e)) {
				Pt r = intersectionPt(t.s, t.e, it->s, it->e);
				if (ret_set.find(r) == ret_set.end())
					ret.push_back(r), ret_set.insert(r), pQ.push(r);
				R[r].insert(t);
				R[r].insert(*it);
			}
			if(jt != S.end() && intersection(t.s, t.e, jt->s, jt->e)) {
				Pt r = intersectionPt(t.s, t.e, jt->s, jt->e);
				if (ret_set.find(r) == ret_set.end())
					ret.push_back(r), ret_set.insert(r), pQ.push(r);
				R[r].insert(t);
				R[r].insert(*jt);
			}
			S.insert(t);
		} else {
			set<seg, CMP>::iterator it, jt, kt;
			it = S.lower_bound(segs[e[i].i]);
			jt = prevNode(it, S);
			kt = nextNode(it, S);
			if(jt != S.end() && kt != S.end() && intersection(kt->s, kt->e, jt->s, jt->e)) {
				Pt r = intersectionPt(kt->s, kt->e, jt->s, jt->e);
				if (ret_set.find(r) == ret_set.end())
					ret.push_back(r), ret_set.insert(r), pQ.push(r);
				R[r].insert(*kt);
				R[r].insert(*jt);
			}
			if(it != S.end())
				S.erase(it);
		}
	} 
	return ret;
}
int main() {
	freopen("in.txt", "r+t", stdin);
	freopen("out2.txt", "w+t", stdout); 

	int testcase, n;
	double sx, sy, ex, ey;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		vector<seg> segs;
		for(int i = 0; i < n; i++) {
			scanf("%lf %lf %lf %lf", &sx, &sy, &ex, &ey);
			segs.push_back(seg(Pt(sx, sy), Pt(ex, ey)));
		}
		vector<Pt> ret = segment_intersect(segs);
		sort(ret.begin(), ret.end());
		printf("%d\n", ret.size());
//		break;
		for (int i = 0; i < ret.size(); i++)
			ret[i].print();
		puts("");
	}
	return 0;
}
/*
50
4
0 4 6 0
0 0 6 4
2 6 8 0
2 -2 4 2

2
0 0 0 1
0 1 2 3

6
1 4 2 -2
5 4 7 -4
5.5 -4 6 0
4 -2 9 3
3 4 6 0
2 1 6 0


Output
3 2
3.75 1.5
4.8 3.2
*/
