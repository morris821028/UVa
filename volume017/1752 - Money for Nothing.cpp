#include <bits/stdc++.h> 
using namespace std;

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

const int MAXN = 500005;
struct Pt {
	int x, y;
	Pt() {}
	Pt(int x, int y): x(x), y(y) {}
} L[MAXN], R[MAXN];

inline int64_t f(int a, int b) {
	if (R[b].x <= L[a].x && R[b].y <= L[a].y)
		return 0;
	return (int64_t) (R[b].x-L[a].x)*(R[b].y-L[a].y);
}

int64_t dc(int x, int y, int l, int r) {
	if (x > y)
		return 0;
	int m = (x+y)/2, mx = l;
	int64_t mxval = f(m, l);
	for (int i = l+1; i <= r; i++) {
		int64_t tmp;
		if ((tmp = f(m, i)) > mxval)
			mxval = tmp, mx = i;
	}
	int64_t ret = mxval;
	ret = max(ret, dc(x, m-1, mx, r));
	ret = max(ret, dc(m+1, y, l, mx));
	return ret;
}

int main() {
	int n, m;
	int x, y;
//	while (scanf("%d %d", &n, &m) == 2) {
	while (ReadInt(&n)) {
		ReadInt(&m); 
		for (int i = 0; i < n; i++) {
//			scanf("%d %d", &x, &y);
			ReadInt(&x), ReadInt(&y);
			L[i] = Pt(x, y);
		}
		for (int i = 0; i < m; i++) {
//			scanf("%d %d", &x, &y);
			ReadInt(&x), ReadInt(&y);
			R[i] = Pt(x, y);
		}
		
		// make a monotone curve
		int _n = 0, _m = 0;
		sort(L, L+n, [](const Pt &a, const Pt &b) {
			if (a.x != b.x)
				return a.x < b.x;
			return a.y < a.y;
		});
		_n = n > 0;
		for (int i = 1; i < n; i++) {
			if (L[i].y < L[_n-1].y)
				L[_n++] = L[i];
		}
		n = _n;
		
		sort(R, R+m, [](const Pt &a, const Pt &b) {
			if (a.x != b.x)
				return a.x > b.x;
			return a.y > a.y;
		});
		_m = m > 0;
		for (int i = 1; i < m; i++) {
			if (R[i].y > R[_m-1].y)
				R[_m++] = R[i];
		}
		m = _m;
		
		int64_t ret = dc(0, n-1, 0, m-1);
		printf("%lld\n", ret);
	}
	return 0;
}
/*
2  2
1  3
2  1
3  5
7  2

1  2
10  10
9  11
11  9
*/
