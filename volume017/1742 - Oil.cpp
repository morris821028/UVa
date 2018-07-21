#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 2005;

struct Oil {
	int xl, xr, y;
	Oil() {}
	Oil(int xl, int xr, int y):
		xl(xl), xr(xr), y(y) {}
	bool operator<(const Oil &o) const {
		return xl < o.xl;
	}
} A[MAXN];

struct Pt {
	int x, y, w;
	Pt() {}
	Pt(int x, int y, int w):
		x(x), y(y), w(w) {}
};

bool cmp(const Pt &a, const Pt &b) {
	int64_t c = (int64_t) a.x * b.y - (int64_t) a.y * b.x;
	if (c != 0)
		return c < 0;
	return a.w > b.w;
}
    
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			int xl, xr, y;
			scanf("%d %d %d", &xl, &xr, &y);
			if (xl > xr)
				swap(xl, xr);
			A[i] = Oil(xl, xr, y);
		}
		
		sort(A, A+n);

		int ret = 0;
		for (int i = 0; i < n; i++) {
			static Pt B[MAXN*2];
			int m = 0;
			int sum = 0;
			for (int j = 0; j < n; j++) {
				int w = A[j].xr - A[j].xl;
				if (A[j].y == A[i].y) {
					if (A[j].xl <= A[i].xl && A[i].xl <= A[j].xr)
						sum += w;
				} else if (A[j].y > A[i].y) {
					B[m++] = Pt(A[j].xl-A[i].xl, A[j].y-A[i].y, w);
					B[m++] = Pt(A[j].xr-A[i].xl, A[j].y-A[i].y, -w);
				} else {
					B[m++] = Pt(A[i].xl-A[j].xr, A[i].y-A[j].y, w);
					B[m++] = Pt(A[i].xl-A[j].xl, A[i].y-A[j].y, -w);
				}
			}
			stable_sort(B, B+m, cmp);
			ret = max(ret, sum);
			
			for (int j = 0; j < m; j++) {
				sum += B[j].w;
				if (B[j].w > 0)
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
