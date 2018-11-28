#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500005;
const int MAXQ = 500005;
struct Planet {
	int32_t x, y, z;
	Planet() {}
	Planet(int x, int y, int z):
		x(x), y(y), z(z) {}
	int64_t dist2(const Planet &p) const {
		return (int64_t) (x-p.x)*(x-p.x) + (int64_t) (y-p.y)*(y-p.y) + (int64_t) (z-p.z)*(z-p.z);
	}
} P[MAXN];

struct Query {
	int32_t r1, r2;
	int i;
	Query() {}
	Query(int32_t r1, int32_t r2, int i): r1(r1), r2(r2), i(i) {
	}
	bool operator<(const Query &q) const {
		if (r1 != q.r1)
			return r1 < q.r1;
		return r2 < q.r2;
	}
	int64_t d1() {
		return (int64_t) r1*r1; 
	}
	int64_t d2() {
		return (int64_t) r2*r2; 
	}
} Q[MAXQ];

struct BIT {
	int tree[MAXN], n;
	void init(int n) {
		this->n = n;
		memset(tree, 0, sizeof(tree[0])*(n+1));
	}
	int sum(int x) {
		int ret = 0;
		while (x)
			ret += tree[x], x -= x&(-x);
		return ret;
	}
	void inc(int x) {
		while (x <= n)
			tree[x]++, x += x&(-x);
	}
} tree;

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
	int n, m;
//	while (scanf("%d", &n) == 1) {
	while (ReadInt(&n)) {
		for (int i = 0; i < n; i++) {
			int32_t x, y, z;
//			scanf("%d %d %d", &x, &y, &z);
			ReadInt(&x), ReadInt(&y) , ReadInt(&z);
			P[i] = Planet(x, y, z);
		}

		static int64_t D1[MAXN], D2[MAXN];
		static pair<int64_t, int64_t> D[MAXN];
		for (int i = 2; i < n; i++) {
			int64_t d1 = P[0].dist2(P[i]);
			int64_t d2 = P[1].dist2(P[i]);
			D1[i-2] = d1, D2[i-2] = d2;
			D[i-2] = {d1, d2};
		}
		n -= 2;
//		scanf("%d", &m);
		ReadInt(&m);
		for (int i = 0; i < m; i++) {
			int r1, r2;
//			scanf("%d %d", &r1, &r2);
			ReadInt(&r1) , ReadInt(&r2);
			Q[i] = Query(r1, r2, i);
		}

		static int ret[MAXQ];
		sort(D1, D1+n);
		sort(D2, D2+n);

		for (int i = 0; i < m; i++) {
			int c = upper_bound(D1, D1+n, Q[i].d1()) - D1;
			ret[i] = c;
		}
		for (int i = 0; i < m; i++) {
			int c = upper_bound(D2, D2+n, Q[i].d2()) - D2;
			ret[i] += c;
		}

		sort(D, D+n);
		sort(Q, Q+m);

		n = unique(D2, D2+n) - D2;
		tree.init(n);

		for (int i = 0, j = 0; i < m; i++) {
			while (j < n && D[j].first <= Q[i].d1()) {
				int p = upper_bound(D2, D2+n, D[j].second) - D2;
				tree.inc(p);
				j++;
			}
			int p = upper_bound(D2, D2+n, Q[i].d2()) - D2;
			ret[Q[i].i] -= tree.sum(p);
		}

		for (int i = 0; i < m; i++)
			bprint.printInt(ret[i], '\n');
//			printf("%d\n", ret[i]);
	}
	return 0;
}
/*
5
1 1 1
5 5 5
2 2 2
3 3 3
4 4 4
4
1 1
2 1
2 2
6 6
*/
