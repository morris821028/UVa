#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 2005;

struct Oil {
	int xl, xr, y;
	Oil() {}
	Oil(int xl, int xr, int y):
		xl(xl), xr(xr), y(y) {}
	bool operator<(const Oil &o) const {
		return y < o.y;
	}
};

struct Pt {
	float s;
	int w;
	Pt() {}
	Pt(int x, int y, int w):
		w(w) {s = (float) x / y;}
	inline void copy(int x, int y, int w) {
		this->s = (float) x / y;
		this->w = w;
	}
};

void radix_sort(Pt *A, int n) {
	for (int i = 0; i < n; i++) {
		int32_t &v = *((int32_t *) &(A[i].s));
		if ((v>>31)&1)
			v = ~v;
		else
			v = v | 0x80000000;
	}
	static Pt _tmp[MAXN*2];
	static const int CHUNK = 256;
	static int C[1<<8];
	Pt *B = _tmp, *T;
	for (int x = 0; x < 4; x++) {
		const int d = x*8;
		memset(C, 0, sizeof(C));
		for (int i = 0; i < n; i++)
			C[((*((int32_t *) &(A[i].s)))>>d)&(CHUNK-1)]++;
		for (int i = 1; i < CHUNK; i++)
			C[i] += C[i-1];
		for (int i = n-1; i >= 0; i--)
			B[--C[((*((int32_t *) &(A[i].s)))>>d)&(CHUNK-1)]] = A[i];
		T = A, A = B, B = T;
	}
	for (int i = 0; i < n; i++) {
		int32_t &v = *((int32_t *) &(A[i].s));
		if ((v>>31)&1)
			v = v & 0x7fffffff;
		else
			v = ~v;
	}
}

Oil A[MAXN];

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
	int n;
//	while (scanf("%d", &n) == 1) {
	while (ReadInt(&n)) {
		for (int i = 1; i <= n; i++) {
			int xl, xr, y;
			ReadInt(&xl), ReadInt(&xr), ReadInt(&y);
//			scanf("%d %d %d", &xl, &xr, &y);
			if (xl > xr)
				swap(xl, xr);
			A[i] = Oil(xl, xr, y);
		}
		
		sort(A, A+n);

		int ret = 0;
		for (int i = 1; i <= n; i++) {
			static Pt B[MAXN*2];
			int m = 0;
			int sum = A[i].xr - A[i].xl;
			const int xl = A[i].xl;
			const int y = A[i].y;
			for (int j = 1; j <= n; j++) {	
				int w = A[j].xr - A[j].xl;
				if (A[j].y == y) {
					continue;
				} else if (A[j].y > y) {
					B[m].copy(A[j].xl-xl, A[j].y-y, w), m++;
				} else {
					B[m].copy(xl-A[j].xr, y-A[j].y, w), m++;
				}
			}
			
			for (int j = 1; j <= n; j++) {	
				int w = A[j].xr - A[j].xl;
				if (A[j].y == y) {
					continue;
				} else if (A[j].y > y) {
					B[m].copy(A[j].xr-xl, A[j].y-y, -w), m++;
				} else {
					B[m].copy(xl-A[j].xl, y-A[j].y, -w), m++;
				}
			}
			
			// run stable sort, make the postive value of Pt.w is in front of 
			// negtive one when they are same Pt.s.
			radix_sort(B, m);
			ret = max(ret, sum);
			
			for (int j = 0; j < m; j++) {
				sum += B[j].w;
				ret = max(ret, sum);
			}	
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
5
100  180  20
30  60  30
70  110  40
10  40  50
0  80  70
3
50  60  10
-42  -42  20
25  0  10
*/

