#include <bits/stdc++.h> 
#include <stdint.h>
using namespace std;
// dp[i] = max(dp[j] + r[j] - p[j] + (d[i] - d[j] - 1)*g[j])
// dp[i] = max(dp[j] + r[j] - p[j] - (d[j] + 1)*g[j] + d[i]*g[j])
const int MAXN = 131072;
struct Sale {
	int64_t d, p, r, g;
	Sale(int d=0, int p=0, int r=0, int g=0):
		d(d), p(p), r(r), g(g) {}
	bool operator<(const Sale &s) const {
		return d < s.d;
	}
};
struct Line {
	int64_t b, x;	// y = b + x*d
	Line(int64_t b=0, int64_t x=0):
		b(b), x(x) {}
	bool operator<(const Line &l) const {
		if (x != l.x)
			return x < l.x;
		return b > l.b;
	}
	int64_t interpolate(int64_t d) {
		return b + x*d;
	}
};
Sale S[MAXN];
int64_t dp[MAXN];
static inline int right(Line l1, Line l2, Line l3) {
	// check the day-axis value
	return (double) (l2.b - l1.b)*(l1.x - l3.x) > (double) (l3.b - l1.b)*(l1.x - l2.x);
}
void merge(int l, int mid, int r, Line q[], int qn) {
	if (qn == 0 || mid+1 > r)
		return ;
	int ql = 0, qr = qn;
	for (int i = mid+1; i <= r; i++) {
		int d = S[i].d;
		int64_t u = q[ql].interpolate(d), v;
		while (ql+1 < qr && u < (v = q[ql+1].interpolate(d)))
			ql++, u = v;
		dp[i] = max(dp[i], u);
	}
}
Line _mem[MAXN];
int convex(Line l[], int lsz, Line r[], int rsz, Line ret[]) {
	static Line con[MAXN];
	int lidx = 0, ridx = 0;
	int n = 0;
	while (lidx < lsz || ridx < rsz) {
		Line t; 
		if (ridx == rsz || (lidx < lsz && l[lidx] < r[ridx]))
			t = l[lidx++];
		else
			t = r[ridx++];
		if (n > 0 && con[n-1].x == t.x)
			continue;
		while (n > 1 && right(con[n-2], con[n-1], t))
			n--;
		con[n] = t, n++;
	}
	memcpy(ret, con, sizeof(con[0])*n);
	return n;
}
int CDQ(int l, int r, Line con[]) {
	if (l == r) {
		if (dp[l] >= S[l].p) {
			con[0] = Line(dp[l] + S[l].r - S[l].p - (S[l].d+1)*S[l].g, S[l].g);
			return 1;
		}
		return 0;
	}
	int mid = (l+r)/2;
	Line *lcon = _mem+l, *rcon = _mem+mid+1;
	int lsz = CDQ(l, mid, lcon);
	merge(l, mid, r, lcon, lsz);
	int rsz = CDQ(mid+1, r, rcon);
	return convex(lcon, lsz, rcon, rsz, con);
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
	int cases = 0;
	int N, C, D;
	while (ReadInt(&N) == 1 && N) {
		ReadInt(&C), ReadInt(&D);
//	while (scanf("%d %d %d", &N, &C, &D) == 3 && N) {
		for (int i = 0; i < N; i++) {
			int d, p, r, g;
//			scanf("%d %d %d %d", &d, &p, &r, &g);
			ReadInt(&d), ReadInt(&p);
			ReadInt(&r), ReadInt(&g);
			S[i] = Sale(d, p, r, g);
		}
		S[N] = Sale(0, 0, C, 0);
		S[N+1] = Sale(D+1, 0, 0, 0);
		N += 2;
		sort(S, S+N);
		memset(dp, 0, sizeof(dp[0])*N);
		CDQ(0, N-1, _mem);
		printf("Case %d: %lld\n", ++cases, dp[N-1]);
	}
	return 0;
}
/*
6  10  20
6  12  1  3
1  9  1  2
3  2  1  2
8  20  5  4
4  11  7  4
2  10  9  1

0 0 0
*/
