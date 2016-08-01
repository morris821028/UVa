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
    int tid, sid;
    Seg(Pt a, Pt b, int c = 0, int d = 0):s(a), e(b), tid(c), sid(d) {}
    
    static double x;
    
    double interpolate(const Pt& p1, const Pt& p2, double& x) const {
        if (p1.x == p2.x) return p1.y;
        return p1.y + (double)(p2.y - p1.y) / (p2.x - p1.x) * (x - p1.x);
    }
    
    bool operator<(const Seg &j) const {
        double y1, y2;
        y1 = interpolate(s, e, x), y2 = interpolate(j.s, j.e, x);
        return cmpZero(y1 - y2) < 0;
    }
    
    int intersect(const Seg &a) const {
        Pt as, at, bs, bt;
        as = s, at = e, bs = a.s, bt = a.e;

        if (min(as.x, at.x) > max(bs.x, bt.x) ||
            min(as.y, at.y) > max(bs.y, bt.y) ||
            max(as.x, at.x) < min(bs.x, bt.x) ||
            max(as.y, at.y) < min(bs.y, bt.y))
            return 0;
            
        if(cmpZero(cross(as, at, bs)) * cmpZero(cross(as, at, bt)) <= 0 &&
           cmpZero(cross(at, as, bs)) * cmpZero(cross(at, as, bt)) <= 0 &&
           cmpZero(cross(bs, bt, as)) * cmpZero(cross(bs, bt, at)) <= 0 &&
           cmpZero(cross(bt, bs, as)) * cmpZero(cross(bt, bs, at)) <= 0)
            return 1;
        return 0;
    }
};
struct Event {
    double x;
    int tid, sid;
    Event(double a = 0, int b = 0, int c = 0):
    x(a), tid(b), sid(c) {}
    bool operator<(const Event &a) const {
        return cmpZero(x - a.x) < 0 || (cmpZero(x - a.x) == 0 && sid < a.sid);
    }
};
double Seg::x = 0;

struct Triangle;
struct SweepLine {
    multimap<Seg, Triangle*> S;
    int status;
    void init() {
        double INF = 262144;
        S.clear();
        S.insert(make_pair(Seg(Pt(-INF, -INF), Pt(INF, -INF), -1, -1), (Triangle*)NULL));
        S.insert(make_pair(Seg(Pt(-INF,  INF), Pt(INF,  INF), -1, -1), (Triangle*)NULL));
        status = 0;
    }
    multimap<Seg, Triangle*>::iterator prevNode(multimap<Seg, Triangle*>::iterator it) {
        return it == S.begin() ? it : --it;
    }
    multimap<Seg, Triangle*>::iterator nextNode(multimap<Seg, Triangle*>::iterator it) {
        return it == S.end() ? it : ++it;
    }
    multimap<Seg, Triangle*>::iterator insert(Seg s, Triangle* v = NULL) {
        multimap<Seg, Triangle*>::iterator it, jt, kt;
        it = S.insert(make_pair(s, v));
        jt = prevNode(it), kt = nextNode(it);
        
        while (jt->first.tid == it->first.tid)
        	jt = prevNode(jt);
        while (kt->first.tid == it->first.tid)
        	kt = nextNode(kt);
        	
        if (jt->first.tid != it->first.tid && (it->first).intersect(jt->first))
            status = 1;
        if (kt->first.tid != it->first.tid && (it->first).intersect(kt->first))
            status = 1;
        return it;
    }
    void erase(multimap<Seg, Triangle*>::iterator it) {
        multimap<Seg, Triangle*>::iterator jt, kt;
        jt = prevNode(it), kt = nextNode(it);
        
        if (kt->first.tid != jt->first.tid && (jt->first).intersect(kt->first))
            status = 1;
        
        S.erase(it);
    }
} sweepLine;

const int MAXN = 131072;
int parent[MAXN];
int depth[MAXN];

struct Triangle {
    Pt p[3];
    int id;
    multimap<Seg, Triangle*>::iterator pit[3];
    // [0]: edge(0, 1), [1]: edge(0, 2), [2]: edge(1, 2)
    bool contain(const Pt &x) const {
        return cmpZero(cross(p[0], p[1], x)) * cmpZero(cross(p[0], p[2], x)) <= 0 &&
        cmpZero(cross(p[1], p[0], x)) * cmpZero(cross(p[1], p[2], x)) <= 0;
    }
    bool contain(const Triangle &x) const {
        return contain(x.p[0]) && contain(x.p[1]) && contain(x.p[2]);
    }
    void addEdge(multimap<Seg, Triangle*>::iterator up, multimap<Seg, Triangle*>::iterator down, SweepLine &sweepline) {
        // x->y: x level == y level, or x in y
        up = sweepline.prevNode(up), down = sweepline.nextNode(down);
        if (up->first.tid != id && up->first.tid >= 0) {
            Triangle *u = up->second;
            if (u->contain(*this))
                parent[id] = u->id;
            else
                parent[id] = parent[u->id];
            if (parent[id] >= 0)
                depth[id] = depth[parent[id]]+1;
        }
        
        if (down->first.tid != id && down->first.tid >= 0) { // for disturbance using
            Triangle *u = down->second;
            if (u->contain(*this))
                parent[id] = u->id;
            else
                parent[id] = parent[u->id];
            if (parent[id] >= 0)
                depth[id] = depth[parent[id]]+1;
        }
    }
    void into(int sid, SweepLine &sweepline) { // into sweep line
        if (sid == 0) {
            pit[0] = sweepline.insert(Seg(p[0], p[1], id), this);
            pit[1] = sweepline.insert(Seg(p[0], p[2], id), this);
            if (sweepline.nextNode(pit[0]) == pit[1])
                addEdge(pit[0], pit[1], sweepline);
            else
                addEdge(pit[1], pit[0], sweepline);
        } else if (sid == 1) {
            pit[2] = sweepline.insert(Seg(p[1], p[2], id), this);
            sweepline.erase(pit[0]);
        } else if (sid == 2) {
            sweepline.erase(pit[1]);
            sweepline.erase(pit[2]);
        }
    }
    void read(int a = 0) {
        p[0].read(), p[1].read(), p[2].read();
        id = a;
        sort(p, p + 3); // need order
    }
} tri[MAXN];

int main() {
    int n, cases = 0;
    while (scanf("%d", &n) == 1 && n >= 0) {
        
        vector<Event> events;
        for (int i = 0; i < n; i++) {
            tri[i].read(i);
            for (int j = 0; j < 3; j++)
                events.push_back(Event(tri[i].p[j].x, i, j));
        }
        for (int i = 0; i < n; i++)
            parent[i] = -1, depth[i] = 1;
        
        sweepLine.init();
        
        sort(events.begin(), events.end());
        for (int i = 0; i < events.size(); i++)  {
            Seg::x = events[i].x + eps * 5; // important disturbance
            tri[events[i].tid].into(events[i].sid, sweepLine);
            if (sweepLine.status)
                break;
        }
        
        printf("Case %d: ", ++cases);
        
        if (sweepLine.status) {
            puts("ERROR"); 
        } else {
            int ret = 0;
            for (int i = 0; i < n; i++)
                ret = max(ret, depth[i]);
            printf("%d shades\n", ret+1);
        }
    }
    return 0;
}
/*
2 
125 984 548 211 372 946
228 312 591 135 423 811
3
125 984 548 211 372 946
228 312 591 135 423 811
981 518 725 961 825 216
2
433 236 808 489 411 131
443 385 417 239 870 151
3
687 592 850 974 788 905
433 236 808 489 411 131
443 385 417 239 870 151

3
83 688 797 623 754 633
107 345 160 424 989 405
767 861 663 893 568 862

 0
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
 
 
 2
 0 1 2 0 -1 0
 1 2 1 -2 4 1
 2
 0 1 2 0 -1 0
 1 -2 1 2 4 1
 1
 -1 2 0 -1 2 1
 1
 -1 -2 0 1 2 -1
 
 
 2
 0 0 1 0 0 1  
 0 0 1 0 0 1 
 2
 0 0 1 0 1 1
 1 0 2 0 1 -1
 2
 0 1 1 0 0 -1
 1 1 1 -1 3 0
 
 4
 0 0 6 -3 4 5
 2 2 4 1 4 3
 2 1 3 1 3 0
 0 1 4 6 1 5
 -1
 */
