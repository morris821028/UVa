#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 1<<17;
class ST {
public:
	int64_t tree[MAXN<<1][2];
	int64_t lazy[MAXN<<1];
	int n;
	void init(int n) {
		init(1, 1, n);
		this->n = n;
	}
	void init(int k, int l, int r) {
		lazy[k] = 0;
		if (l == r) {
			tree[k][0] = 100;
			tree[k][1] = 100*l;
			return ;
		}
		int mid = (l+r)>>1;
		init(k<<1, l, mid);
		init(k<<1|1, mid+1, r);
		tree[k][0] = tree[k<<1][0] + tree[k<<1|1][0];
		tree[k][1] = tree[k<<1][1] + tree[k<<1|1][1];
	}
	void add(int l, int r, int w) {
		if (w)
			add(1, 1, n, l, r, w);
	}
	void add(int k, int l, int r, int x, int y, int w) {
		if (x <= l && r <= y) {
			lazy[k] += w;
			tree[k][0] += w*(r-l+1);
			tree[k][1] += (int64_t) w*(r-l+1)*(l+r)/2;
			return ;
		}
		int mid = (l+r)>>1;
		if (lazy[k]) {
			int64_t w = lazy[k];
			lazy[k] = 0;
			lazy[k<<1] += w;
			lazy[k<<1|1] += w;
			tree[k<<1][0] += w*(mid-l+1);
			tree[k<<1][1] += (int64_t) w*(mid-l+1)*(l+mid)/2;
			tree[k<<1|1][0] += w*(r-mid);
			tree[k<<1|1][1] += (int64_t) w*(r-mid)*(mid+1+r)/2;
		}
		if (x <= mid)
			add(k<<1, l, mid, x, y, w);
		if (y > mid)
			add(k<<1|1, mid+1, r, x, y, w);
		tree[k][0] = tree[k<<1][0] + tree[k<<1|1][0];
		tree[k][1] = tree[k<<1][1] + tree[k<<1|1][1];
	}
	int64_t sum(int l, int r) {
		return sum(1, 1, n, l, r);
	}
	int64_t sum(int k, int l, int r, int x, int y) {
		if (x <= l && r <= y)
			return tree[k][1] - tree[k][0]*(x-1);
		int mid = (l+r)>>1;
		int64_t ret = 0;
		if (lazy[k]) {
			int64_t w = lazy[k];
			lazy[k] = 0;
			lazy[k<<1] += w;
			lazy[k<<1|1] += w;
			tree[k<<1][0] += w*(mid-l+1);
			tree[k<<1][1] += (int64_t) w*(mid-l+1)*(l+mid)/2;
			tree[k<<1|1][0] += w*(r-mid);
			tree[k<<1|1][1] += (int64_t) w*(r-mid)*(mid+1+r)/2;
		}
		if (x <= mid)
			ret += sum(k<<1, l, mid, x, y);
		if (y > mid)
			ret += sum(k<<1|1, mid+1, r, x, y);
		return ret;
	}
} st;

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
    void printInt(int64_t x, char padding) {
        static char stk[16];
        int idx = 0, neg = x < 0;
        if (x < 0)	x = -x;
        stk[idx++] = padding;
        if (!x)	
            stk[idx++] = '0';
        while (x)
            stk[idx++] = x%10 + '0', x /= 10;
        if (neg)
        	stk[idx++] = '-';
        while (idx) {
            if (p == end) {
                *p = '\0';
                printf("%s", buf), p = buf;
            }
            *p = stk[--idx], p++;
        }
    }
    void print(char *s) {
    	while (*s) {
    		if (p == end) {
                *p = '\0';
                printf("%s", buf), p = buf;
            }
            *p = *s, p++, s++;
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
	int cases = 0;
	int testcase, n, m;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d", &n, &m);
		ReadInt(&n), ReadInt(&m);
		st.init(n);
//		printf("Case %d:\n", ++cases);
		bprint.print("Case ");
		bprint.printInt(++cases, ':');
		bprint.print("\n");
		for (int i = 0; i < m; i++) {
//			static char cmd[16];
			char cmd;
			int l, r, w;
//			scanf("%s", cmd);
			while ((cmd = readchar()) < 'a');
			while (readchar() != ' ');
			if (cmd == 'q') {
//				scanf("%d %d", &l, &r);
				ReadInt(&l), ReadInt(&r);
//				printf("%lld\n", st.sum(l, r));
				bprint.printInt(st.sum(l, r), '\n');
			} else {
//				scanf("%d %d %d", &l, &r, &w);
				ReadInt(&l), ReadInt(&r), ReadInt(&w);
				st.add(l, r, w);
			}
		}
	}
	return 0;
}
/*
1
5 5
query 1 3
change 2 3 4
query 1 3
query 2 3
query 3 3
*/
