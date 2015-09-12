#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
#define eps 1e-12
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
    double dist2(Pt a) {
        return (x - a.x)*(x - a.x)+(y - a.y)*(y - a.y);
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
Pt getIntersect(Pt as, Pt ae, Pt bs, Pt be) {
    Pt u = as - bs;
    double t = cross2(be - bs, u)/cross2(ae - as, be - bs);
    return as + (ae - as) * t;
}
int cmpZero(double x) {
    if (fabs(x) < eps)  return 0;
    return x < 0 ? -1 : 1;
}
struct Polygon {
    vector<Pt> p;
    void split(Pt st, Pt ed, Polygon &pa, Polygon &pb) {
        pa.p.clear(), pb.p.clear();
        int n = (int) p.size();
        for (int i = 0; i < n; i++) {
            int pos = cmpZero(cross(st, ed, p[i]));
            if (pos >= 0) {
                pa.p.push_back(p[i]);
            }
            if (pos <= 0) {
                pb.p.push_back(p[i]);
            }
            if (cmpZero(cross(st, ed, p[i]))*cmpZero(cross(st, ed, p[(i+1)%n])) < 0) {
                Pt t = getIntersect(st, ed, p[i], p[(i+1)%n]);
                pa.p.push_back(t), pb.p.push_back(t);
            }
        }
        pa.p.resize(unique(pa.p.begin(), pa.p.end()) - pa.p.begin());
        pa.p.resize(unique(pa.p.begin(), pa.p.end()) - pa.p.begin());
    }
    bool intersect(Pt st, Pt ed) {
        int n = (int) p.size(), flag = 0;
        for (int i = 0; i < n; i++) {
            int t = cmpZero(cross(st, ed, p[i]));
            if (t < 0)  flag |= 1;
            if (t > 0)  flag |= 2;
        }
        return flag == 3;
    }
    void print() {
        for (int i = 0; i < p.size(); i++)
            printf("[%.1lf %.1lf] ", p[i].x, p[i].y);
        puts("");
    }
};
struct Node {
    Polygon poly;
    Node *lson, *rson;
    Node() {
        lson = rson = NULL;
    }
} nodes[65536];
int nodesize = 0;
Node* newNode() {
    Node *p = &nodes[nodesize++];
    *p = Node();
    return p;
}
void dfs(Node *u, Pt st, Pt ed) {
    if (u == NULL)  return ;
    if (u->lson == NULL && u->rson == NULL) {
        if (u->poly.intersect(st, ed)) {
            Polygon ta, tb;
            u->poly.split(st, ed, ta, tb);
            u->lson = newNode();
            u->rson = newNode();
            u->lson->poly = ta;
            u->rson->poly = tb;
        }
    } else {
        if (!u->poly.intersect(st, ed))
            return ;
        dfs(u->lson, st, ed);
        dfs(u->rson, st, ed);
    }
}
int countTri(Node *u) {
    if (u == NULL)  return 0;
    if (u->lson == NULL && u->rson == NULL) {
        return u->poly.p.size() == 3;
    } else {
        return countTri(u->lson) + countTri(u->rson);
    }
}
int main() {
    int N, M, K;
    while (scanf("%d %d %d", &N, &M, &K) == 3) {
        Polygon poly;
        
        poly.p.push_back(Pt(0, 0));
        poly.p.push_back(Pt(0, M));
        poly.p.push_back(Pt(N, M));
        poly.p.push_back(Pt(N, 0));
        
        Node *root = newNode();
        root->poly = poly;
        for (int i = 0; i < K; i++) {
            Pt st, ed;
            st.read(), ed.read();
            dfs(root, st, ed);
        }
        int ret = countTri(root);
        printf("%d\n", ret);
    }
    return 0;
}
/*
 4 4 4
 0 0 4 4
 0 2 4 2
 0 2 2 4
 1 4 4 1
 */

