#include <bits/stdc++.h>
using namespace std;

struct Pt {
	int x, y;
	Pt() {}
	Pt(int x, int y): x(x), y(y) {}
	bool operator<(const Pt &p) const {
		if (x != p.x)	return x < p.x;
		return y < p.y;
	}
};

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
    
struct QuadTree {
	static const int MAXN = 2005;
	struct Node {
		Node *ch[4];
		vector<Pt> s;
		int size;
		Node() {}
		void init() {
			memset(ch, 0, sizeof(ch));
			s.clear();
			size = 0;
		}
	} nodes[MAXN];
	struct QE {
		int a, b, c;
		bool operator<(const QE &x) const {
			if (a != x.a)	return a < x.a;
			if (b != x.b)	return b < x.b;
			return c < x.c;
		}
	};
	struct QA {
		int p, q, r;
	};
	Node *root;
	int nodesize;
	map<QE, QA> store;
	void init() {
		nodesize = 0, root = NULL;
		store.clear();
	}
	Node* newNode() {
		Node *p = &nodes[nodesize++];
		p->init();
		return p;
	}
	Node* _build(vector<Pt> &p) {
		int n = p.size();
		if (n == 0)	return NULL;
		Node *u = newNode();
		u->size = n;
		int mid = n/2;
		Pt mm = p[mid];
		u->s.push_back(mm);
		vector<Pt> ch[4];
		for (int i = 0; i < n; i++) {
			if (i == mid)
				continue;
			if (p[i].x < mm.x && p[i].y < mm.y)	
				ch[2].push_back(p[i]);
			else if (p[i].x < mm.x && p[i].y > mm.y)
				ch[1].push_back(p[i]);
			else if (p[i].x > mm.x && p[i].y < mm.y)
				ch[3].push_back(p[i]);
			else if (p[i].x > mm.x && p[i].y > mm.y)
				ch[0].push_back(p[i]);
			else
				u->s.push_back(p[i]);
		}
		p.clear();
		u->ch[0] = _build(ch[0]);
		u->ch[1] = _build(ch[1]);
		u->ch[2] = _build(ch[2]);
		u->ch[3] = _build(ch[3]);
		return u;
	}
	void build(Pt p[], int n) {
		init();
		vector<Pt> q(p, p+n);
		sort(q.begin(), q.end());
		root = _build(q);
	}

	int a, b, c;
	int p, q, r;
	int eval(Pt p) {
		return a*p.x + b*p.y + c;
	}
	int size(Node *p) {
		if (p == NULL)	return 0;
		return p->size;
	}
	void _query(Node *u) {
		if (u == NULL)
			return;
		int t = eval(u->s[0]);
		for (auto v : u->s) {
			int z = eval(v);
			if (z == 0)		r++;
			else if (z < 0)	p++;
			else			q++;
		}
		if (t == 0) {
			if (a == 0) {	// x-axis
				p += size(u->ch[2]) + size(u->ch[3]); // -
				q += size(u->ch[0]) + size(u->ch[1]); // +
				return;
			} else if (b == 0) {	// y-axis
				p += size(u->ch[1]) + size(u->ch[2]);
				q += size(u->ch[0]) + size(u->ch[3]);
				return;
			} else if (a*b > 0) {
				_query(u->ch[1]);
				_query(u->ch[3]);
				p += size(u->ch[2]);
				q += size(u->ch[0]);
			} else {
				_query(u->ch[0]);
				_query(u->ch[2]);
				p += size(u->ch[1]);
				q += size(u->ch[3]);
			}
		} else if (t > 0) {
			if (a == 0) {
				q += size(u->ch[0]) + size(u->ch[1]);
				_query(u->ch[2]), _query(u->ch[3]);
			} else if (b == 0) {
				q += size(u->ch[0]) + size(u->ch[3]);
				_query(u->ch[1]), _query(u->ch[2]);
			} else if (a*b > 0) {
				q += size(u->ch[0]);
				_query(u->ch[1]), _query(u->ch[2]), _query(u->ch[3]);
			} else {
				q += size(u->ch[3]);
				_query(u->ch[0]), _query(u->ch[1]), _query(u->ch[2]);
			}
		} else {
			if (a == 0) {
				p += size(u->ch[2]) + size(u->ch[3]);
				_query(u->ch[0]), _query(u->ch[1]);
			} else if (b == 0) {
				p += size(u->ch[1]) + size(u->ch[2]);
				_query(u->ch[0]), _query(u->ch[3]);
			} else if (a*b > 0) {
				p += size(u->ch[2]);
				_query(u->ch[0]), _query(u->ch[1]), _query(u->ch[3]);
			} else {
				p += size(u->ch[1]);
				_query(u->ch[0]), _query(u->ch[2]), _query(u->ch[3]);
			}
		}
	}
	void query(int x1, int y1, int x2, int y2)  {
		a = -(y2 - y1), b = x2 - x1;
		c = -(a*x1 + b*y1);
		int g = __gcd(__gcd(a, b), c);
		a /= g, b /= g, c /= g;
		// ax + by + c = 0
		if (a < 0)	a = -a, b = -b, c = -c;
		if (a == 0 && b < 0)	b = -b, c = -c;
		auto prev = store.find({a, b, c});
		if (prev != store.end()) {
//			printf("%d %d %d\n", prev->second.p, prev->second.q, prev->second.r);
			bprint.printInt(prev->second.p, ' ');
			bprint.printInt(prev->second.q, ' ');
			bprint.printInt(prev->second.r, '\n');
			return;
		}
		p = q = r = 0;
		_query(root);
		if (p > q)	swap(p, q);
//		printf("%d %d %d\n", p, q, r);
		bprint.printInt(p, ' ');
		bprint.printInt(q, ' ');
		bprint.printInt(r, '\n');
		store[{a, b, c}] = {p, q, r};
	}
} tree;

int main() {
	int testcase, cases = 0;
	int n, x, y;
	Pt p[2005];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			p[i] = Pt(x, y);
		}

		tree.build(p, n);
		
		int m, x1, y1, x2, y2;
		int dx1, dy1, dx2, dy2;
		const int MOD = 10000;
		scanf("%d %d %d %d %d %d %d %d %d", &m, &x1, &y1, &x2, &y2, &dx1, &dy1, &dx2, &dy2);
		printf("Case #%d:\n", ++cases);
		for (int i = 0; i < m; i++)	{
			x1 = (x1 + dx1)%MOD;
			y1 = (y1 + dy1)%MOD;
			x2 = (x2 + dx2)%MOD;
			y2 = (y2 + dy2)%MOD;
			if (x1 == x2 && y1 == y2)
				y2 = (y1+1)%MOD;
//			printf("Segment((%d, %d),(%d, %d))\n", x1, y1, x2, y2);
			tree.query(x1, y1, x2, y2);			
		}
	}
	return 0;
}
/*
1
4
5 5
5 10
10 5
10 10
2 -7 -7 7 7 1 1 1 1

2
4
5 5
5 10
10 5
10 10
6 -7 -7 7 7 1 2 3 4
4
5 5
5 7
10 5
10 10
5 -7 -7 7 7 1 3 2 4

1
4
5 5
5 7
8 3
10 10
5 -6 -7 4 5 1 3 2 4
*/
