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
int cmpZero(double v) {
	if (fabs(v) > eps) return v > 0 ? 1 : -1;
	return 0;
}
const double pi = acos(-1);

// this problem
const int MAXN = 128;
struct Object {
	vector<Pt> pt;
	char label;
} obj[MAXN];
struct Node {
	Node *l, *r;
	vector<Object*> obj;
	void init() {
		obj.clear();
		l = r = NULL;
	}
} nodes[MAXN];
int nsize;

void splitPlane(Node *u, Seg seg) {
	if (u == NULL)
		return ;
	vector<Object*> front, rear;
	for (int i = 0; i < u->obj.size(); i++) {
		Pt a = u->obj[i]->pt[0];
		Pt b = Pt(a.x, -0x3f3f3f3f);
		if (cmpZero(cross(seg.s, seg.e, a)) *
			cmpZero(cross(seg.s, seg.e, b)) >= 0) {
			front.push_back(u->obj[i]);
		} else {
			rear.push_back(u->obj[i]);
		}
	}
	if (front.size() && rear.size()) {
		Node *l = &nodes[nsize++];
		Node *r = &nodes[nsize++];
		l->init(), r->init();
		l->obj = front, r->obj = rear;
		u->l = l, u->r = r;
		u->obj.clear();
	}
	
	splitPlane(u->l, seg);
	splitPlane(u->r, seg);
}

void print(Node *u) {
	if (u == NULL)
		return;
	for (int i = 0; i < u->obj.size(); i++)
		printf("%c", u->obj[i]->label);
	print(u->r);
	print(u->l);
}
int main() {
	int n, m, p;
	double x, y;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%d", &m);
			obj[i].pt.clear();
			obj[i].label = 'A' + i;
			for (int j = 0; j < m; j++) {
				scanf("%lf %lf", &x, &y);
				obj[i].pt.push_back(Pt(x, y));
			}
		}
		
		nsize = 0;
		Node *root = &nodes[nsize++];
		root->init();
		for (int i = 0; i < n; i++)
			root->obj.push_back(&obj[i]);
		
		scanf("%d", &p);
		for (int i = 0; i < p; i++) {
			Pt s, e;
			s.read(), e.read();
			splitPlane(root, Seg(s, e));
		}
		
		print(root);
		puts("");
	}
	return 0;
}
/*
10
3 65 5 66 5 65 6
3 65 123 66 123 65 124
3 122 176 123 176 122 177
3 56 23 57 23 56 24
3 11 49 12 49 11 50
3 167 111 168 111 167 112
3 57 123 58 123 57 124
3 130 6 131 6 130 7
3 100 85 101 85 100 86
3 11 28 12 28 11 29
10
159 165 -131 -177
-153 -192 -197 158
-77 -86 -98 30
-177 59 146 63
192 -117 92 43
121 -67 -62 -134
41 -81 130 196
95 -185 -89 154
-163 -179 93 175
113 41 -92 -28
*/
