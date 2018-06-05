#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 100005;
const int64_t INF = 1LL<<60;
int tss = 0;
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

void _radix_sort(Pt *A, int n) {
	static Pt _tmp[MAXN];
	const int CHUNK = 256;
	static int C[CHUNK];
	Pt *B = _tmp, *T;
    for (int x = 0; x < 4; x++) {	// HACK, it should be 8 for 64-bit, but this problem could be 4.
        const int d = x*8;
        memset(C, 0, sizeof(C));
        for (int i = 0; i < n; i++)
			C[(A[i].x>>d)&(CHUNK-1)]++;
        for (int i = 1; i < CHUNK; i++)
			C[i] += C[i-1];
//		// decreasing
//	    for (int i = CHUNK-2; i >= 0; i--)
//			C[i] += C[i+1];
        for (int i = n-1; i >= 0; i--)
			B[--C[(A[i].x>>d)&(CHUNK-1)]] = A[i];
        T = A, A = B, B = T;
    }
}
void radix_sort(Pt *A, int n) {
	int m = 0;
	for (int i = 0; i < n; i++) {
		if (A[i].x < 0)
			swap(A[i], A[m]), m++;
	}
	_radix_sort(A, m);
	_radix_sort(A+m, n-m);
}

// priority search tree
struct PST {
#define islson(p) (p->p->lson == p)
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
		if (l <= r) {
			ret->mid = A[(l+r)/2].x;
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
		radix_sort(A, n);
		size = 0;
		root = _build(0, n-1, NULL);
	}
	void shortcut(Node *p) {
		if (p == NULL || p->val != 0)
			return ;
		if (p->p) {
			if (p->sum == 0 || p->rson && p->sum == p->rson->sum) {
				if (islson(p))
					p->p->lson = p->rson;
				else
					p->p->rson = p->rson;
				if (p->rson)
					p->rson->p = p->p;
			} else if (p->lson && p->sum == p->lson->sum) {
				if (islson(p))
					p->p->lson = p->lson;
				else
					p->p->rson = p->lson;
				if (p->lson)
					p->lson->p = p->p;
			}			
		} else if (p->p == NULL) {
			if (p->sum == 0) {
				root = NULL;
			} else if (p->rson && p->sum == p->rson->sum) {
				root = p->rson;
				if (p->rson != NULL)
					p->rson->p = NULL;
			} else if (p->lson && p->sum == p->lson->sum) {
				root = p->lson;
				if (p->lson != NULL)
					p->lson->p = NULL;
			}
		}
	}
	void del(int i) {
		Node *p = loc[i];
		if (p == NULL || p->val == 0)
			return ;
		p->val = 0;
		while (p != NULL) {
			--(p->sum);
			shortcut(p);
			p = p->p;
		}
		loc[i] = NULL;
	}
	int visible(int i) {
		return loc[i] != NULL && loc[i]->val != 0;
	}
	
	int ret[MAXN], ret_n, qi;
	int64_t qlx, qrx, qy;
	int _del_range(Node *u) {
		if (u->sum == 0 || u->dat.y > qy)
			return 0;
		int s = 0;
		if (u->val != 0 && qlx <= u->dat.x && u->dat.x <= qrx) {
			ret[ret_n++] = u->dat.id;
			if (u->dat.id != qi)
				s++, u->val = 0, loc[u->dat.id] = NULL;
		}
		if (u->lson && qlx <= u->mid)
			s += _del_range(u->lson);
		if (u->rson && qrx >= u->mid)
			s += _del_range(u->rson);
		if (s) {
			u->sum -= s;
			shortcut(u);
		}
		return s;		
	}
	void del_range(int64_t lx, int64_t rx, int64_t y, int i) {
		ret_n = 0;
		qlx = lx, qrx = rx, qy = y, qi = i;
		if (root != NULL)
			_del_range(root);
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
    void println(const char *s) {
    	while (*s) {
    		if (p == end) {
                *p = '\0';
                printf("%s", buf), p = buf;
            }
            *p = *s, p++, s++;
		}
		if (p == end) {
            *p = '\0';
            printf("%s", buf), p = buf;
        }
        *p = '\n', p++;
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
//				puts("FAIL");
				bprint.println("FAIL");
				continue;
			}

			Pt l;
			visible++;
			if (hat[i].t == 0) {
				d0trans(&hat[i], &l);
				a0.del_range(l.x, INF, l.y, i);
				for (int j = 0; j < a0.ret_n; j++) {
					int v = a0.ret[j];
					if (v != i) {
						a1.del(v);
						visible -= v < i;
					}
				}
			} else {
				d1trans(&hat[i], &l);
				a1.del_range(l.x, INF, l.y, i);
				for (int j = 0; j < a1.ret_n; j++) {
					int v = a1.ret[j];
					if (v != i) {
						a0.del(v);
						visible -= v < i;
					}
				}
			}
			bprint.printInt(visible, '\n');
//			printf("%d\n", visible);
		}
	}
//	fprintf(stderr, "It took me %d clicks (%f seconds).\n",tsum,((float)tsum)/CLOCKS_PER_SEC);
	fprintf(stderr, "%d\n", tss);
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
