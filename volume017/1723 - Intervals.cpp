#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;
const int MAXV = 50005;
struct Interval {
	int l, r, c;
	Interval() {}
	Interval(int l, int r, int c):
		l(l), r(r), c(c) {}
} A[MAXN];

void radix_sort(Interval A[], int n) {
	static Interval B[MAXN];
	static int C[MAXV];
	memset(C, 0, sizeof(C));
	for (int i = 0; i < n; i++)
		C[A[i].r]++;
	for (int i = 1; i < MAXV; i++)
		C[i] += C[i-1];
	for (int i = 0; i < n; i++)
		B[--C[A[i].r]] = A[i];
	for (int i = 0; i < n; i++)
		A[i] = B[i];
}

struct Solver {
	static const int size = 256;
	uint16_t tree[MAXV];
	uint16_t parent[MAXV];
	void init() {
		memset(tree, 0, sizeof(tree));
		for (int i = 0; i < MAXV; i++)
			parent[i] = i;
	}
	int sum(int x) {
		int ret = 0;
		while (x > 0)
			ret += tree[x], x -= x&(-x);
		return ret + tree[0];
	}
	void inc(int x) {
		while (x < MAXV)
			tree[x]++, x += x&(-x);
	}
	int count(int l, int r) {
		return sum(r) - sum(l-1);
	}
	int next(int x) {
		return parent[x] == x ? x : (parent[x] = next(parent[x]));
	}
	int fill(int l, int r, int c) {
		int f = count(l, r);
		if (f >= c)
			return 0;
		int s = c-f;
		int ret = s;
		r = next(r);
		while (s > 0 && r >= l) {
			inc(r);
			parent[r] = next(r-1);
			r = parent[r];
			s--;
		}
		return ret;
	}
} tool;


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
			int l, r, c;
//			scanf("%d %d %d", &l, &r, &c);
			ReadInt(&l), ReadInt(&r), ReadInt(&c);
			l++, r++;
			A[i] = Interval(l, r, c);
		}

		radix_sort(A, n);
		int ret = 0;
		tool.init();
		for (int i = 0; i < n; i++)
			ret += tool.fill(A[i].l, A[i].r, A[i].c);
		printf("%d\n", ret);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1
5
3  7  3
8  10  3
6  8  1
1  3  1
10  11  1

99999

10
6 10 4
54 83 3
29 71 2
3 13 0
8 47 21
32 60 7
7 51 28
48 59 2
31 72 29
23 67 34

10
22 64 37
46 63 11
70 97 21
38 66 9
42 59 16
27 36 0
40 99 56
53 58 0
51 58 5
18 89 36

9999
10
129 227 50
455 489 29
714 882 15
70 869 207
140 595 29
395 905 414
52 321 113
88 144 46
134 947 776
160 187 27

10
450 703 207
469 533 2
221 808 415
210 698 361
129 300 148
248 798 419
142 688 72
560 889 196
72 262 92
342 545 131
*/

