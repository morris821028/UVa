#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
#define eps 1e-6
const double pi = acos(-1);
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
    void print() {
    	printf("%.0lf %.0lf\n", x, y);
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
int cmpZero(double x) {
    if (fabs(x) < eps)	return 0;
    return x < 0 ? -1 : 1;
}

struct Seg {
    Pt s, e;
    int sid;
    Seg(Pt a = Pt(), Pt b = Pt(), int c = 0):s(a), e(b), sid(c) {}
    
    static double x;
    
    double interpolate(double x) const {
    	return interpolate(s, e, x);
	}
    double interpolate(const Pt& p1, const Pt& p2, double& x) const {
        if (p1.x == p2.x) return p1.y;
        return p1.y + (double)(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
    }
    
    bool operator<(const Seg &j) const {
        double y1, y2;
        y1 = interpolate(s, e, x), y2 = interpolate(j.s, j.e, x);
        return y1 - y2 > 0;
    }
    
    int intersect(const Seg &a) const {
        Pt as, at, bs, bt;
        as = s, at = e, bs = a.s, bt = a.e;

        if (min(as.x, at.x) > max(bs.x, bt.x) ||
            min(as.y, at.y) > max(bs.y, bt.y) ||
            max(as.x, at.x) < min(bs.x, bt.x) ||
            max(as.y, at.y) < min(bs.y, bt.y))
            return 0;
            
        if(cmpZero(cross(as, at, bs)) * cmpZero(cross(as, at, bt)) < 0 &&
           cmpZero(cross(at, as, bs)) * cmpZero(cross(at, as, bt)) < 0 &&
           cmpZero(cross(bs, bt, as)) * cmpZero(cross(bs, bt, at)) < 0 &&
           cmpZero(cross(bt, bs, as)) * cmpZero(cross(bt, bs, at)) < 0)
            return 1;
        return 0;
    }
};
Pt getIntersect(Seg a, Seg b) {
	Pt u = a.s - b.s;
    double t = cross2(b.e - b.s, u)/cross2(a.e - a.s, b.e - b.s);
    return a.s + (a.e - a.s) * t;
}
struct Event {
    double x;
    int qid, sid;
    Event(double a = 0, int b = 0, int c = 0):
    x(a), qid(b), sid(c) {}
    bool operator<(const Event &a) const {
    	if (cmpZero(x - a.x) != 0)
    		return cmpZero(x - a.x) < 0;
    	if (qid != a.qid)
    		return qid < a.qid;
        return sid < a.sid;
    }
};
double Seg::x = 0;

struct SweepLine {
    multimap<Seg, int> S;
    int status;
    
    void init() {
        double INF = 262144;
        S.clear();
        S.insert(make_pair(Seg(Pt(-INF, -INF), Pt(INF, -INF), -1), -1));
        S.insert(make_pair(Seg(Pt(-INF,  INF), Pt(INF,  INF), -1), -1));
    }
    multimap<Seg, int>::iterator prevNode(multimap<Seg, int>::iterator it) {
        return it == S.begin() ? it : --it;
    }
    multimap<Seg, int>::iterator nextNode(multimap<Seg, int>::iterator it) {
        return it == S.end() ? it : ++it;
    }
    multimap<Seg, int>::iterator insert(Seg s, set<Event> &events, int v = -1) {
        multimap<Seg, int>::iterator it, jt, kt;
        it = S.insert(make_pair(s, v));
        jt = prevNode(it), kt = nextNode(it);
                	
        if (jt->first.sid != it->first.sid && (it->first).intersect(jt->first)) {
        	Pt a = getIntersect(it->first, jt->first);
        	if (a.x > Seg::x) {
        		events.insert(Event(a.x, -1, jt->first.sid));
        		events.insert(Event(a.x,  1, jt->first.sid));
        		events.insert(Event(a.x, -1, it->first.sid));
        		events.insert(Event(a.x,  1, it->first.sid));
        	}
        }
        if (kt->first.sid != it->first.sid && (it->first).intersect(kt->first)) {
            Pt a = getIntersect(it->first, kt->first);
            if (a.x > Seg::x) {
				events.insert(Event(a.x, -1, kt->first.sid));
        		events.insert(Event(a.x,  1, kt->first.sid));
        		events.insert(Event(a.x, -1, it->first.sid));
        		events.insert(Event(a.x,  1, it->first.sid));
        	}
        }
        return it;
    }
    void erase(multimap<Seg, int>::iterator it, set<Event> &events) {
        multimap<Seg, int>::iterator jt, kt;
        jt = prevNode(it), kt = nextNode(it);
        
        if (kt->first.sid != jt->first.sid && (jt->first).intersect(kt->first)) {
            Pt a = getIntersect(kt->first, jt->first);
            if (a.x > Seg::x) {
        		events.insert(Event(a.x, -1, jt->first.sid));
        		events.insert(Event(a.x,  1, jt->first.sid));
        		events.insert(Event(a.x, -1, kt->first.sid));
        		events.insert(Event(a.x,  1, kt->first.sid));
        	}	
        }
        
        S.erase(it);
    }
} sweepLine;

const int MAXN = 65536;
Seg segs[MAXN];
multimap<Seg, int>::iterator sit[MAXN];

void skyline(Seg segs[], int n) {
	set<Event> events;
	double tot_len = 0;
	for (int i = 0; i < n; i++) {
        if (segs[i].e < segs[i].s)
        	swap(segs[i].s, segs[i].e);
        events.insert(Event(segs[i].s.x,  1, i));
        events.insert(Event(segs[i].e.x, -1, i));
        tot_len += (segs[i].s - segs[i].e).length();
    }
    sweepLine.init();
        
    int top_id = -1;
    double prev_x;
    double skyline_len = 0;
    while (events.size() > 0) {
    	double x = events.begin()->x;
    	Seg::x = x + eps * 5;
//    	printf("time %lf\n", x);
    	while (events.size() && events.begin()->x <= x) {
    		Event e = *events.begin();
    		events.erase(events.begin());
//    		printf("event %lf %d %d\n", e.x, e.sid, e.qid);
    		if (e.qid == 1) {
    			sit[e.sid] = sweepLine.insert(segs[e.sid], events, e.sid);
	    	} else {
    			sweepLine.erase(sit[e.sid], events);
    		}
    	}
//    	printf("%lf %d\n", x, top_id);
    	if (top_id != -1) {
    		double y1 = segs[top_id].interpolate(prev_x);
			double y2 = segs[top_id].interpolate(x);
			skyline_len += hypot(prev_x - x, y1 - y2);
			printf("[%lf %lf] %lf %lf\n", prev_x, x, y1, y2);
    	}
    	top_id = sweepLine.nextNode(sweepLine.S.begin())->first.sid;
    	prev_x = x;
    }
    double hidden_len = tot_len - skyline_len;
    printf("%.3lf\n", hidden_len);
}
int main() {
	int testcase;
    int n, cases = 0;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &n);
        
        for (int i = 0; i < n; i++) {
            Pt a, b;
            a.read();
            b.read();
            segs[i] = Seg(a, b, i);
        }
        skyline(segs, n);
    }
    return 0;
}
/*
2
3
1 2 4 8
1 6 7 2
8 5 10 2
3
0 1 100000 0
0 0 2 100000
1 100000 3 0 

999

5
0 3 4 5
1 2 6 5
2 6 6 3
3 2 4 2
6 2 8 4

4
8 10 11 4
9 5 13 10
8 8 13 8
12 5 14 4

2
15 3 16 4
16 4 17 5

2
0 0 1 1
5 5 10 10 
 */
