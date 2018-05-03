#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 100005;
struct Pt {
	int x, y;
	Pt(int x=0, int y=0):
		x(x), y(y) {}
	bool operator<(const Pt &o) const {
		return abs(x) + abs(y) < abs(o.x) + abs(o.y);
		return min(abs(x), abs(y)) < min(abs(o.x), abs(o.y));
	}
} m[MAXN];
struct Rect {
	int lx, ly, rx, ry;
	Rect(int lx=0, int ly=0, int rx=0, int ry=0):
		lx(lx), ly(ly), rx(rx), ry(ry) {}
} r[MAXN];

int valid(Rect *r, int n, int lx, int ly, int rx, int ry) {
	if (n == 0)	
		return 1;
	if (r[0].rx < lx || r[0].lx > rx || r[0].ry < ly || r[0].ly > ry)
		return valid(r+1, n-1, lx, ly, rx, ry);
	int ret = 0;
	if (!ret && r[0].lx > lx && r[0].lx <= rx) {
		ret |= valid(r+1, n-1, lx, ly, r[0].lx-1, ry);
		lx = r[0].lx;
	}
	if (!ret && r[0].rx >= lx && r[0].rx < rx) {
		ret |= valid(r+1, n-1, r[0].rx+1, ly, rx, ry);
		rx = r[0].rx;
	}
	if (!ret && r[0].ly > ly && r[0].ly <= ry) {
		ret |= valid(r+1, n-1, lx, ly, rx, r[0].ly-1);
		ly = r[0].ly;
	}
	if (!ret && r[0].ry >= ly && r[0].ry < ry) {
		ret |= valid(r+1, n-1, lx, r[0].ry+1, rx, ry);
		ry = r[0].ry;
	}
	return ret;
}
int trans(int d, int n) {
	for (int i = 0; i <= n; i++) {
		r[i].lx = m[i].x - d, r[i].rx = m[i].x + d;
		r[i].ly = m[i].y - d, r[i].ry = m[i].y + d;
	}
	return valid(r+1, n, r[0].lx, r[0].ly, r[0].rx, r[0].ry);
}

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
	int n, cases = 0;
//	while (scanf("%d", &n) == 1 && n >= 0) {
	while (ReadInt(&n) == 1 && n >= 0) {
		for (int i = 1; i <= n; i++) {
			int x, y;
//			scanf("%d %d", &x, &y);
			ReadInt(&x), ReadInt(&y);
			m[i] = Pt(x, y);
		}
		sort(m+1, m+n+1);
		const int INF = 1000005;
		int l = 1, r = INF;
		int ret = INF;
		while (l <= r) {
			int mid = (l+r)/2;
			if (trans(mid, n)) {
				ret = mid;
				l = mid+1;
			} else {
				r = mid-1;
			}
		}
		printf("Case %d: ", ++cases);
		if (ret == INF)
			puts("never");
		else
			printf("%d\n", ret+1);
	}
	return 0;
}
