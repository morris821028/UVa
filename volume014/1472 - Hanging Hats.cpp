#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
const int64_t INF = 1LL<<60;
struct Hat {
	int64_t x, y;
	int t;
	Hat(int64_t x=0, int64_t y=0, int t=0):
		x(x), y(y), t(t) {}
} hat[MAXN];
struct Pt {
	int64_t x, y;
	int id;
};
static void d0trans(Hat *h, Pt *p) {
	p->x = h->x - h->y;
	p->y = h->x + h->y;
}
static void d1trans(Hat *h, Pt *p) {
	p->x = h->x*2 - h->y;
	p->y = h->x*2 + h->y;
}
// priority search tree
struct PST {
	struct Node {
		Node *lson, *rson, *p;
		Pt dat;
		int64_t mid; 
		int sum, val;
	};
	Pt A[MAXN];
	Node _nodes[MAXN], *loc[MAXN];
	Node *root;
	int size;
	static bool cmpX(const Pt &x, const Pt &y) {
		return x.x < y.x;
	}
	Node* _build(int l, int r, Node *p) {
		if (l > r)
			return NULL;
		Node *ret = &_nodes[size++];
		int64_t mnY, mnX;
		int mnIdx, mnId;
		
		mnY = A[l].y, mnIdx = l;
		for (int i = l+1; i <= r; i++) {
			if (A[i].y < mnY)	
				mnY = A[i].y, mnIdx = i;
		}
		mnX = A[mnIdx].x, mnId = A[mnIdx].id;
		ret->dat = A[mnIdx];
		memmove(A+mnIdx, A+mnIdx+1, sizeof(A[0])*(r-mnIdx));
		r--;
		loc[mnId] = ret;
		ret->p = p;
		ret->mid = A[(l+r)/2].x;
		if (l <= r) {
			ret->lson = _build(l, (l+r)/2, ret);
			ret->rson = _build((l+r)/2+1, r, ret);
		} else {
			ret->lson = NULL;
			ret->rson = NULL;
		}
		ret->sum = r-l+2, ret->val = 1;
		return ret;
	}
	void build(int n, Hat h[], void (trans)(Hat*, Pt *)) {
		for (int i = 0; i < n; i++) {
			trans(&h[i], &A[i]);
			A[i].id = i;
		}
		sort(A, A+n, cmpX);
		size = 0;
		root = _build(0, n-1, NULL);
	}
	void dec(int i) {
		Node *p = loc[i];
		if (p->val == 0)
			return ;
		p->val = 0;
		while (p != NULL)
			p->sum--, p = p->p;
	}
	int visible(int i) {
		return loc[i]->val != 0;
	}
	
	int ret[MAXN], ret_n;
	int64_t qlx, qrx, qy;
	void _range(Node *u) {
		if (u->sum == 0 || u->dat.y > qy)
			return ;
		if (u->val != 0 && qlx <= u->dat.x && u->dat.x <= qrx)
			ret[ret_n++] = u->dat.id;
		if (u->lson && qlx <= u->mid)
			_range(u->lson);
		if (u->rson && qrx >= u->mid)
			_range(u->rson);
	}
	void range(int64_t lx, int64_t rx, int64_t y) {
		ret_n = 0;
		qlx = lx, qrx = rx, qy = y;
		_range(root);
	}
} a0, a1;

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
int main() {
	int testcase;
	int n;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d", &n);
		ReadInt(&n);
		
		for (int i = 0; i < n; i++) {
			static char s[16];
			int x, y;
//			scanf("%d %d %s", &x, &y, s);
			ReadInt(&x), ReadInt(&y), s[0] = readchar();
			if (s[0] == 'W')
				hat[i] = Hat(x, y, 0);
			else
				hat[i] = Hat(x, y, 1);
		}
		a0.build(n, hat, d0trans);
		a1.build(n, hat, d1trans);
		
		int visible = 0;
		for (int i = 0; i < n; i++) {
			if (!a0.visible(i) || !a1.visible(i)) {
				puts("FAIL");
				continue;
			}

			Pt l;
			visible++;
			if (hat[i].t == 0) {
				d0trans(&hat[i], &l);
				a0.range(l.x, INF, l.y);
				for (int j = 0; j < a0.ret_n; j++) {
					int v = a0.ret[j];
					if (v != i) {
						a0.dec(v), a1.dec(v);
						visible -= v < i;
					}
				}
			} else {
				d1trans(&hat[i], &l);
				a1.range(l.x, INF, l.y);
				for (int j = 0; j < a1.ret_n; j++) {
					int v = a1.ret[j];
					if (v != i) {
						a0.dec(v), a1.dec(v);
						visible -= v < i;
					}
				}
			}
			printf("%d\n", visible);
		}
	}
	return 0;
}
/*
2

3
0 1 W
0 2 N
0 1 W


7
4 3 W
8 8 N
3 2 W
9 5 W
12 1 W
14 2 N
13 4 W
*/
