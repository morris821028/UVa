#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;
#define eps 1e-8
#define MAXV 262144
#define MAXE (262144*32) 
#define OPT_IO
namespace {
#define TYPE_P float
	struct Point {
	    TYPE_P x, y;
	    Point(TYPE_P a = 0, TYPE_P b = 0):
	    x(a), y(b) {}
	    Point operator-(const Point &a) const {
	        return Point(x - a.x, y - a.y);
	    }
	    Point operator+(const Point &a) const {
	        return Point(x + a.x, y + a.y);
	    }
	    Point operator*(const TYPE_P a) const {
	        return Point(x * a, y * a);
	    }
	    bool operator<(const Point &a) const {
	        if (fabs(x - a.x) > eps)	return x < a.x;
	        if (fabs(y - a.y) > eps)	return y < a.y;
	        return false;
	    }
	    bool operator==(const Point &a) const {
	        return fabs(x - a.x) < eps && fabs(y - a.y) < eps;
	    }
	    bool operator!=(const Point &a) const {
	        return !(fabs(x - a.x) < eps && fabs(y - a.y) < eps);
	    }
	    inline double dist(Point b) const {
	        return hypot(x - b.x, y - b.y);
	    }
	    inline TYPE_P dist2(Point b) const {
	        return (x - b.x) * (x - b.x) + (y - b.y) * (y - b.y);
	    }
	};
	struct Point3D {
	    TYPE_P x, y, z;
	    Point3D(TYPE_P a = 0, TYPE_P b = 0, TYPE_P c = 0):
	    x(a), y(b), z(c) {}
	    Point3D(Point p) {
	        x = p.x, y = p.y, z = p.x * p.x + p.y * p.y;
	    }
	    Point3D operator-(const Point3D &a) const {
	        return Point3D(x - a.x, y - a.y, z - a.z);
	    }
	    inline double dot(Point3D a) const {
	        return x * a.x + y * a.y + z * a.z;
	    }
	};
	inline int cmpZero(TYPE_P v) {
	    if (fabs(v) > eps)	return v > 0 ? 1 : -1;
	    return 0;
	}
	inline TYPE_P cross(Point o, Point a, Point b) {
	    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
	}
	inline Point3D cross(Point3D a, Point3D b) { // normal vector
	    return Point3D(a.y * b.z - a.z * b.y
	                   , -a.x * b.z + a.z * b.x
	                   , a.x * b.y - a.y * b.x);
	}
	inline int inCircle(Point a, Point b, Point c, Point p) {
	    if (cross(a, b, c) < 0)
	        swap(b, c);
	    Point3D a3(a), b3(b), c3(c), p3(p);
	    b3 = b3 - a3, c3 = c3 - a3, p3 = p3 - a3;
	    // -- check same direction, in: < 0, on: = 0, out: > 0
	    return p3.dot(cross(b3, c3)) < 0;
	}
	// -- seg(a, b) and seg(c, d)
	inline int intersection(Point a, Point b, Point c, Point d) {
	    return cmpZero(cross(a, c, b))*cmpZero(cross(a, b, d)) > 0
	    	&& cmpZero(cross(c, a, d))*cmpZero(cross(c, d, b)) > 0;
	}
#undef TYPE_P
}

class Delaunay {
private:
	Point *idxBuf[MAXV];
	int idxRename[MAXV];
	static bool cmp(Point *x, Point *y) { return *x < *y; }
	struct Edge {
	    int id;
	    Edge *twin, *next, *prev;
	    Edge(int id = 0): id(id) {twin = next = prev = NULL;}
	} edges[MAXE];
	int esize = 0;
	inline Edge *newEdge(int v) {
		Edge *e = &edges[esize++];
		*e = Edge(v);
		return e;
	}
	inline Edge* insertEdge(int u, int v) {
		Edge *e = newEdge(v);
		e->next = head[u]->next;
		if (head[u]->next != NULL)
			head[u]->next->prev = e;
		head[u]->next = e, e->prev = head[u];
		return e;
	}
	inline void eraseEdge(Edge *e) {
		e->prev->next = e->next;
		if (e->next != NULL)
			e->next->prev = e->prev;
	}
	inline Edge* newEdgeHead() {
		return newEdge(-1);
	}
public:
	// -- graph
    Edge *head[MAXV];
    Point p[MAXV];
    int n;
    void init(int n, Point p[]) {
        this->n = n, this->esize = 0;
        for (int i = 0; i < n; i++)
            head[i] = newEdgeHead();
        for (int i = 0; i < n; i++)
            idxBuf[i] = p+i;
        sort(idxBuf, idxBuf + n, cmp);
        for (int i = 0; i < n; i++) {
        	idxRename[i] = idxBuf[i] - p;
        	this->p[i] = *(idxBuf[i]);
        }
        divide(0, n - 1);
    }
    inline void addEdge(int u, int v) {
    	Edge *p = insertEdge(u, v);
    	Edge *q = insertEdge(v, u);
    	p->twin = q, q->twin = p;
    }
    void divide(int l, int r) {
        if (r - l <= 2) { // -- #point <= 3
            for (int i = l; i <= r; i++)
                for (int j = i+1; j <= r; j++)
                    addEdge(i, j);
            return;
        }
        const int mid = (l + r)>>1;
        divide(l, mid);
        divide(mid + 1, r);
        
        Edge *it;
        int nowl = l, nowr = r;
        
        static int que[MAXV];
        int qidx = 0;
        // -- find left and right convex, lower common tangent
        for (int i = l; i <= r; i++) {
        	while (qidx >= 2 && cross(p[que[qidx-2]], p[que[qidx-1]], p[i]) < 0)
        		qidx--;
        	que[qidx++] = i;
		}
		for (int i = 1; i < qidx; i++) {
			if (que[i-1] <= mid && que[i] > mid) {
				nowl = que[i-1], nowr = que[i];
				break;
			}
		}
        // -- add lower common tangent
        addEdge(nowl, nowr);
        for (; ; ) {
            const Point ptL = p[nowl], ptR = p[nowr];
            int ch = -1, side = -1;
            for (it = head[nowl]->next; it != NULL; it = it->next) {
            	Point t = p[it->id];
                if (cross(ptL, ptR, t) > 0
                    && (ch == -1 || inCircle(ptL, ptR, p[ch], t)))
                    ch = it->id, side = 0;
            }
            for (it = head[nowr]->next; it != NULL; it = it->next) {
            	Point t = p[it->id];
                if (cross(ptR, t, ptL) > 0
                    && (ch == -1 || inCircle(ptL, ptR, p[ch], t)))
                    ch = it->id, side = 1;
            }
            // -- arrive upper common tangent
            if (ch == -1)	break;
            if (side == 0) {
                for (it = head[nowl]->next; it != NULL; it = it->next) {
                    if (intersection(ptL, p[it->id], ptR, p[ch]))
                    	eraseEdge(it->twin), eraseEdge(it);
                }
                nowl = ch, addEdge(nowl, nowr);
            } else {
                for (it = head[nowr]->next; it != NULL; it = it->next) {
                    if (intersection(ptR, p[it->id], ptL, p[ch]))
                        eraseEdge(it->twin), eraseEdge(it);
                }
                nowr = ch, addEdge(nowl, nowr);
            }
        }
    }
    
    vector< pair<int, int> > getEdge() {
        vector< pair<int, int> > ret;
        Edge *it;
        ret.reserve(n*3);
        for (int i = 0; i < n; i++) {
            for (it = head[i]->next; it != NULL; it = it->next) {
                if (it->id < i)
                    continue;
                ret.push_back(make_pair(idxRename[i], idxRename[it->id]));
            }
        }
        return ret;
    }
} tool;

namespace {
    inline int readchar() {
        const int N = 1048576;
        static char buf[N];
        static char *p = buf, *end = buf;
        if(p == end) {
            if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
            p = buf;
        }
        return *p++;
    }
    inline int ReadInt(int *x) {
        static char c, neg;
        while((c = readchar()) < '-')    {if(c == EOF) return 0;}
        neg = (c == '-') ? -1 : 1;
        *x = (neg == 1) ? c-'0' : 0;
        while((c = readchar()) >= '0')
            *x = (*x << 3) + (*x << 1) + c-'0';
        *x *= neg;
        return 1;
    }
    class Print {
    public:
        static const int N = 1048576;
        char buf[N], *p, *end;
        Print() {
            p = buf, end = buf + N - 1;
        }
        void printInt(int x, char padding) {
            static char stk[16];
            int idx = 0;
            stk[idx++] = padding;
            if (!x)	
                stk[idx++] = '0';
            while (x)
                stk[idx++] = x%10 + '0', x /= 10;
            while (idx) {
                if (p == end) {
                    *p = '\0';
                    printf("%s", buf), p = buf;
                }
                *p = stk[--idx], p++;
            }
        }
        void printLongLong(long long x, char padding) {
            static char stk[20];
            int idx = 0;
            stk[idx++] = padding;
            if (!x)	
                stk[idx++] = '0';
            while (x)
                stk[idx++] = x%10 + '0', x /= 10;
            while (idx) {
                if (p == end) {
                    *p = '\0';
                    printf("%s", buf), p = buf;
                }
                *p = stk[--idx], p++;
            }
        }
        static inline void online_printInt(int x) {
            static char ch[16];
            static int idx;
            idx = 0;
            if (x == 0)	ch[++idx] = 0;
            while (x > 0) ch[++idx] = x % 10, x /= 10;
            while (idx) 
                putchar(ch[idx--]+48);
        }
        ~Print() {
            *p = '\0';
            printf("%s", buf);
        }
    } bprint;
}
int main() {
//	freopen("1.in", "r", stdin);
//	freopen("test.out", "w", stdout);
    int testcase, n;
    int x, y;
	static Point p[MAXV];

#ifndef OPT_IO
    scanf("%d", &n);
#else
	ReadInt(&n);
#endif
    for (int i = 0; i < n; i++) {
#ifndef OPT_IO
        scanf("%d %d", &x, &y);
#else
		ReadInt(&x), ReadInt(&y);
#endif
        p[i] = Point(x, y);
    }
    tool.init(n, p);
    vector< pair<int, int> > DG = tool.getEdge();
       
	long long ret = 1LL<<60;
    int ret_x, ret_y;
    vector< pair<int, int> > ret_p;
    for (int i = 0, sz = DG.size(); i < sz; i++) {
        x = DG[i].first, y = DG[i].second;
        if (x > y)
        	swap(x, y);
        long long dx = p[x].x - p[y].x, dy = p[x].y - p[y].y;
        long long v = dx*dx + dy*dy;
        if (v < ret)
        	ret = v, ret_p.clear();
        if (v == ret)
        	ret_p.push_back(make_pair(x, y));
    }
    sort(ret_p.begin(), ret_p.end());
    printf("%.2lf %zu\n", sqrt(ret), ret_p.size());
    for (auto e: ret_p)
    	printf("%d %d\n", e.first+1, e.second+1);
    return 0;
}
