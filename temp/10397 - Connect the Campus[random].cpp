#include <stdio.h> 
#include <math.h>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <assert.h>
using namespace std;

#define eps 1e-16
#define MAXN 65536
struct Pt {
    double x, y;
    int label;
    Pt(double a = 0, double b = 0, int c = -1):
    	x(a), y(b), label(c) {}	
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
    Pt operator*(const double a) const {
        return Pt(x * a, y * a);
    }
	Pt operator/(const double a) const {
        return Pt(x / a, y / a);
    }
    bool operator<(const Pt &a) const {
		if (fabs(x - a.x) > eps)
			return x < a.x;
		if (fabs(y - a.y) > eps)
			return y < a.y;
		return false;
	}
	bool operator==(const Pt &a) const {
		return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	}
	bool operator!=(const Pt &a) const {
		return !(fabs(x - a.x) < eps && fabs(y - a.y) < eps);
	} 
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double dist2(Pt a, Pt b) {
	return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}
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
Pt getIntersection(Pt p, Pt l1, Pt q, Pt l2) {
	double a1, a2, b1, b2, c1, c2;
	double dx, dy, d;
	a1 = l1.y, b1 = -l1.x, c1 = a1 * p.x + b1 * p.y;
	a2 = l2.y, b2 = -l2.x, c2 = a2 * q.x + b2 * q.y;
	d = a1 * b2 - a2 * b1;
	dx = b2 * c1 - b1 * c2;
	dy = a1 * c2 - a2 * c1;
	return Pt(dx / d, dy / d);
}
Pt circle(Pt a, Pt b, Pt c) {
	Pt mab = (a + b)/2;
	Pt mbc = (b + c)/2;
	Pt lab = b - a, lbc = c - b;
	swap(lab.x, lab.y);
	swap(lbc.x, lbc.y);
	lab.x = -lab.x;
	lbc.x = -lbc.x;
	return getIntersection(mab, lab, mbc, lbc);
}
struct Seg {
	Pt s, e;
	double angle;
	int label;
	Seg(Pt a = Pt(), Pt b = Pt(), int l=0):s(a), e(b), label(l) {
		angle = atan2(e.y - s.y, e.x - s.x);
	}
	bool operator<(const Seg &other) const {
		if (fabs(angle - other.angle) > eps)
			return angle > other.angle;
		if (cross(other.s, other.e, s) > -eps)
			return true;
		return false;
	}
}; 
class Delaunay {
	public: 
	struct Node;
	struct Triangle;
	struct Triangle {
		Pt *a, *b, *c;
		Node *tab, *tac, *tbc;
		Triangle(Pt *pa = NULL, Pt *pb = NULL, Pt *pc = NULL) {
			a = pa, b = pb, c = pc;
			tab = tac = tbc = NULL;
		}
		void print() {
			printf("Triangle (%lf %lf) (%lf %lf) (%lf %lf)\n"
					, a->x, a->y
					, b->x, b->y
					, c->x, c->y);
		}
		bool operator==(const Triangle &x) const {
			return (*a == *x.a && *b == *x.b && *c == *x.c) || 
				   (*a == *x.a && *c == *x.b && *b == *x.c) ||
				   (*b == *x.a && *a == *x.b && *c == *x.c) || 
				   (*b == *x.a && *c == *x.b && *a == *x.c) ||
				   (*c == *x.a && *a == *x.b && *b == *x.c) || 
				   (*c == *x.a && *b == *x.b && *a == *x.c);
		}
		int contains(Pt p) { // include edge
			if (onSeg(*a, *b, p) || onSeg(*b, *c, p) || onSeg(*c, *a, p))
				return 1;
			if (cross(*a, p, *b) * cross(*a, p, *c) < -eps &&
				cross(*b, p, *a) * cross(*b, p, *c) < -eps &&
				cross(*c, p, *a) * cross(*c, p, *b) < -eps)
				return 1;
			return 0;
		}
		int interior(Pt p) { // not include edge
			if (cross(*a, p, *b) * cross(*a, p, *c) < -eps &&
				cross(*b, p, *a) * cross(*b, p, *c) < -eps &&
				cross(*c, p, *a) * cross(*c, p, *b) < -eps)
				return 1;
			return 0;
		}
	};
	struct Node {
		Triangle tri;
		vector<Node*> son;
		Node(Triangle a=Triangle()) {
			tri = a;
		}
		void adjust(Node* x, Pt a, Pt b) {
			if (x == NULL)	return;
			if ((*x->tri.a == a && *x->tri.b == b) ||
				(*x->tri.a == b && *x->tri.b == a))
				x->tri.tab = this;
			if ((*x->tri.b == a && *x->tri.c == b) ||
				(*x->tri.b == b && *x->tri.c == a))
				x->tri.tbc = this;
			if ((*x->tri.a == a && *x->tri.c == b) ||
				(*x->tri.a == b && *x->tri.c == a))
				x->tri.tac = this;
		}
		void setNeighbor(Node* a, Node *b, Node *c) {
			tri.tab = c;
			tri.tbc = a;
			tri.tac = b;
			adjust(a, *tri.b, *tri.c);
			adjust(b, *tri.a, *tri.c);
			adjust(c, *tri.a, *tri.b);
		}
		Node* getNeighbor(Pt *pi, Pt *pj) {
			if ((tri.a == pi && tri.b == pj) || (tri.a == pj && tri.b == pi))
				return tri.tab;
			if ((tri.b == pi && tri.c == pj) || (tri.b == pj && tri.c == pi))
				return tri.tbc;
			if ((tri.a == pi && tri.c == pj) || (tri.a == pj && tri.c == pi))
				return tri.tac;
//			puts("WARNING : NODE::getNeighbor");
			return NULL;
		}
		Pt* getAnotherPoint(Pt *pi, Pt *pj) {
			if ((tri.a == pi && tri.b == pj) || (tri.a == pj && tri.b == pi))
				return tri.c;
			if ((tri.b == pi && tri.c == pj) || (tri.b == pj && tri.c == pi))
				return tri.a;
			if ((tri.a == pi && tri.c == pj) || (tri.a == pj && tri.c == pi))
				return tri.b;
//			assert(false);
//			puts("WARNING : NODE::AnotherPoint");
			return NULL;
		}
	} nodes[MAXN], *root;
	int nodesize;
	/* <input> */
	vector<Pt> P;
	int n;
	/* <output> */
	vector<Triangle> Tri;
	vector<Node*>	Leaf;
	vector< pair<int, int> > Edge;
	char outputLabel;
	void init(vector<Pt> p) {
		Tri.clear(), Leaf.clear(), Edge.clear();
		if (p.size() < 1)	return;
		outputLabel = 'A';
		nodesize = 0;
		P = p;
		double mx = p[0].x, my = p[0].y;
		for (int i = 0; i < p.size(); i++)
			mx = max(mx, (double) p[i] .x), my = max(my, (double) p[i].y);
		mx += 1, my += 1;
		Pt a, b, c;
		a = Pt(mx, my), b = Pt(mx-1, my), c = Pt(mx, my-1);
		Triangle tri(&a, &b, &c);
		for (int i = 0; i < p.size(); i++) {
			if (!tri.interior(p[i])) {
				double cc = p[i].x + p[i].y; // y = -x + cc
				b = Pt(cc - my - 1, my), c = Pt(mx, cc - mx - 1);
			}
		}
		for (int i = 0; i < p.size(); i++) {
			int x = rand()%p.size(), y = rand()%p.size();
			swap(p[x], p[y]);
		} // after this, vector<Pt> can't change.
		n = p.size();
		p.push_back(a), p.push_back(b), p.push_back(c);
		nodes[nodesize] = Node(Triangle(&p[n], &p[n+1], &p[n+2]));
		root = &nodes[nodesize];
		nodesize++;
		run();
	}
	void findPointLocation(Node *u, Pt p, vector<Node*> &ret) {
		assert(u != NULL);
		if (u->son.size() == 0 && u->tri.contains(p))
			ret.push_back(u);
		for (int i = 0; i < u->son.size(); i++) {
			if ((u->son[i])->tri.contains(p)) {
				findPointLocation(u->son[i], p, ret);
				return ;
			}
		}
	}
	vector<Node*> findTriangleContains(Pt p) {
		vector<Node*> ret;
		findPointLocation(root, p, ret);
		if (ret.size() > 0 && ret[0]->tri.interior(p))
			return ret;
		if (ret.size() == 1) {
			Node *u = ret[0], *v = NULL;
			
			if (onSeg(*u->tri.a, *u->tri.b, p))
				v = u->getNeighbor(u->tri.a, u->tri.b);
			if (onSeg(*u->tri.b, *u->tri.c, p))
				v = u->getNeighbor(u->tri.b, u->tri.c);
			if (onSeg(*u->tri.c, *u->tri.a, p))
				v = u->getNeighbor(u->tri.c, u->tri.a);
			if (v != NULL)	ret.push_back(v);
		}
		return ret;
	}
	Node* getNode(Triangle t) {
		Node *p;
		nodes[nodesize] = Node(t);
		p = &nodes[nodesize];
		assert(nodesize + 1 < MAXN);
		nodesize++;
		return p;
	}
	void flip(Node *u, Node *v, Pt *pr, Pt *pi, Pt *pj, Pt *pk, Node* &p, Node* &q) {
		p = getNode(Triangle(pr, pi, pk));
		q = getNode(Triangle(pr, pj, pk));
		p->setNeighbor(v->getNeighbor(pi, pk), q, u->getNeighbor(pi, pr));
		q->setNeighbor(v->getNeighbor(pj, pk), p, u->getNeighbor(pj, pr));
		u->son.push_back(p), u->son.push_back(q);
		v->son.push_back(p), v->son.push_back(q);
	}
	void legalizeEdge(Node *u, Pt *pr, Pt *pi, Pt *pj) { // adjust shared edge
		if (u == NULL)	return;
		Node *v;
		Pt *pk, o = circle(*pr, *pi, *pj);
		v = u->getNeighbor(pi, pj);
		if (v == NULL)	return ;
		pk = v->getAnotherPoint(pi, pj);
		if (pk == NULL)	return ;
		if (dist2(o, *pk) < dist2(o, *pr) - eps) { // illegal
			Node *p = NULL, *q = NULL, *np, *nq;
			flip(u, v, pr, pi, pj, pk, p, q);
			legalizeEdge(p, pr, pi, pk);
			legalizeEdge(q, pr, pj, pk);
		}
	}
	void run() {
		vector<Node*> in;
		for (int i = 0; i < n; i++) {
			in = findTriangleContains(P[i]);
			if (in.size() == 1 && in[0]->tri.interior(P[i])) {
				Node *ta, *tb, *tc;
				ta = getNode(Triangle(in[0]->tri.a, in[0]->tri.b, &P[i]));
				tb = getNode(Triangle(in[0]->tri.b, in[0]->tri.c, &P[i]));
				tc = getNode(Triangle(in[0]->tri.c, in[0]->tri.a, &P[i]));
				ta->setNeighbor(tb, tc, in[0]->tri.tab);
				tb->setNeighbor(tc, ta, in[0]->tri.tbc);
				tc->setNeighbor(ta, tb, in[0]->tri.tac);
				in[0]->son.push_back(ta);
				in[0]->son.push_back(tb);
				in[0]->son.push_back(tc);
				legalizeEdge(ta, &P[i], ta->tri.a, ta->tri.b);
				legalizeEdge(tb, &P[i], tb->tri.a, tb->tri.b);
				legalizeEdge(tc, &P[i], tc->tri.a, tc->tri.b);
			} else {
				assert(in.size() == 2);
				Node *t[4] = {};
				for (int j = 0; j < in.size(); j++) {
					if (onSeg(*in[j]->tri.a, *in[j]->tri.b, P[i])) {
						t[2*j]   = getNode(Triangle(in[j]->tri.c, in[j]->tri.a, &P[i]));
						t[2*j+1] = getNode(Triangle(in[j]->tri.c, in[j]->tri.b, &P[i]));
						t[2*j]->setNeighbor(NULL, t[2*j+1], in[j]->tri.tac);
						t[2*j+1]->setNeighbor(NULL, t[2*j], in[j]->tri.tbc);
					} else if (onSeg(*in[j]->tri.b, *in[j]->tri.c, P[i])) {
						t[2*j]   = getNode(Triangle(in[j]->tri.a, in[j]->tri.b, &P[i]));
						t[2*j+1] = getNode(Triangle(in[j]->tri.a, in[j]->tri.c, &P[i]));
						t[2*j]->setNeighbor(NULL, t[2*j+1], in[j]->tri.tab);
						t[2*j+1]->setNeighbor(NULL, t[2*j], in[j]->tri.tac);
					} else if (onSeg(*in[j]->tri.a, *in[j]->tri.c, P[i])) {
						t[2*j]   = getNode(Triangle(in[j]->tri.b, in[j]->tri.a, &P[i]));
						t[2*j+1] = getNode(Triangle(in[j]->tri.b, in[j]->tri.c, &P[i]));
						t[2*j]->setNeighbor(NULL, t[2*j+1], in[j]->tri.tab);
						t[2*j+1]->setNeighbor(NULL, t[2*j], in[j]->tri.tbc);
					}
					in[j]->son.push_back(t[2*j]);
					in[j]->son.push_back(t[2*j+1]);
				}
				if (t[0]->tri.a == t[2]->tri.a || t[0]->tri.a == t[2]->tri.b ||
					t[0]->tri.b == t[2]->tri.a || t[0]->tri.b == t[2]->tri.b) {
					t[0]->tri.tbc = t[2], t[2]->tri.tbc = t[0];
					t[1]->tri.tbc = t[3], t[3]->tri.tbc = t[1];
				} else {
					t[0]->tri.tbc = t[3], t[3]->tri.tbc = t[0];
					t[1]->tri.tbc = t[2], t[2]->tri.tbc = t[1];
				}
				for (int j = 0; j < 4; j++)
					legalizeEdge(t[j], &P[i], t[j]->tri.a, t[j]->tri.b);
			}
		}
		generateTriangle();
//		print();
	}
	void generateTriangle() {
		Tri.clear(), Leaf.clear(), Edge.clear();
		queue<Node*> Q;
		set<Node*> S;
		Node *u, *v;
		Q.push(root), S.insert(root);
		while (!Q.empty()) {
			u = Q.front(), Q.pop();
			if (u->son.size() == 0) {
				Tri.push_back(u->tri), Leaf.push_back(u);
				Edge.push_back(make_pair(u->tri.a->label, u->tri.b->label));
				Edge.push_back(make_pair(u->tri.b->label, u->tri.c->label));
				Edge.push_back(make_pair(u->tri.c->label, u->tri.a->label));
			}
			for (int i = 0; i < u->son.size(); i++) {
				if (S.find(u->son[i]) == S.end())  {
					S.insert(u->son[i]);
					Q.push(u->son[i]);
				}
			}
		}
	}
	void print() {
		for (int i = 0; i < Tri.size(); i++) {
			printf("{%.3lf %.3lf, %.3lf %.3lf, %.3lf %.3lf}\n"
				, Tri[i].a->x, Tri[i].a->y
				, Tri[i].b->x, Tri[i].b->y
				, Tri[i].c->x, Tri[i].c->y);
			printf("Neighbor: {\n");
			if (Tri[i].tbc != NULL) {
				printf("	{%.3lf %.3lf, %.3lf %.3lf, %.3lf %.3lf}\n"
				, Tri[i].tbc->tri.a->x, Tri[i].tbc->tri.a->y
				, Tri[i].tbc->tri.b->x, Tri[i].tbc->tri.b->y
				, Tri[i].tbc->tri.c->x, Tri[i].tbc->tri.c->y);
			}
			if (Tri[i].tac != NULL) {
				printf("	{%.3lf %.3lf, %.3lf %.3lf, %.3lf %.3lf}\n"
				, Tri[i].tac->tri.a->x, Tri[i].tac->tri.a->y
				, Tri[i].tac->tri.b->x, Tri[i].tac->tri.b->y
				, Tri[i].tac->tri.c->x, Tri[i].tac->tri.c->y);
			}
			if (Tri[i].tab != NULL) {
				printf("	{%.3lf %.3lf, %.3lf %.3lf, %.3lf %.3lf}\n"
				, Tri[i].tab->tri.a->x, Tri[i].tab->tri.a->y
				, Tri[i].tab->tri.b->x, Tri[i].tab->tri.b->y
				, Tri[i].tab->tri.c->x, Tri[i].tab->tri.c->y);
			}
			puts("}");
		}
		puts("");
	}
} tool;

struct edge {
	int x, y, v;
	edge(int a = 0, int b = 0, int c = 0):
		x(a), y(b), v(c) {}
	bool operator<(const edge &a) const {
		return v < a.v;
	}
};
int parent[1024], weight[1024];
void init(int n) {
    for(int i= 0; i <= n; i++)
        parent[i] = i, weight[i] = 1;
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int joint(int x, int y) {
    x = findp(x), y = findp(y);
    if (x == y)	return 0;
    if(weight[x] > weight[y])
        weight[x] += weight[y], parent[y] = x;
    else
        weight[y] += weight[x], parent[x] = y;
    return 1;
}
int main() {
	int n, m, cases = 0;
	while (scanf("%d", &n) == 1) {
		init(n);
		int x, y;
		int e = 0;
		vector<Pt> D;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			D.push_back(Pt(x, y, i));
		}
		scanf("%d", &m);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			x--, y--;
			e += joint(x, y);
		}
		
		tool.init(D);
		
		vector<edge> E;
		for (int i = 0; i < tool.Edge.size(); i++) {
			x = tool.Edge[i].first, y = tool.Edge[i].second;
			if (x >= 0 && y >= 0) {
				int v = (D[x].x - D[y].x) * (D[x].x - D[y].x) + 
							(D[x].y - D[y].y) * (D[x].y - D[y].y);
				E.push_back(edge(x, y, v));
			}
		}
		sort(E.begin(), E.end());
		double ret = 0;
		for (int i = 0; i < E.size(); i++) {
			x = E[i].x, y = E[i].y;
			if (joint(x, y)) {
				ret += sqrt(E[i].v);
				e++;
				if (e == n - 1)
					break;
			}
		}
		printf("%.2lf\n", ret);
	}
	return 0;
}
/*
2
1 1
2 2
0
1
1 1
0

4
103 104
104 100
104 103
100 100
1
4 2

4
3 4
4 0
4 3
0 0
1
4 2
*/
