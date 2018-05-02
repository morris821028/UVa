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
void merge(int l, int mid, int r, vector<Line> &q) {
	if (q.size() == 0 || mid+1 > r)
		return ;
	int ql = 0, qr = q.size();
	for (int i = mid+1; i <= r; i++) {
		int d = S[i].d;
		int64_t u = q[ql].interpolate(d), v;
		while (ql+1 < qr && u < (v = q[ql+1].interpolate(d)))
			ql++, u = v;
		dp[i] = max(dp[i], u);
	}
}
void convex(vector<Line> &l, vector<Line> &r, vector<Line> &con) {
	int lidx = 0, ridx = 0;
	int lsz = l.size(), rsz = r.size();
	int n = 0;
	while (lidx < lsz || ridx < rsz) {
		Line t; 
		if (ridx == rsz || (lidx < lsz && l[lidx] < r[ridx]))
			t = l[lidx++];
		else
			t = r[ridx++];
		if (n > 0 && con.back().x == t.x)
			continue;
		while (n > 1 && right(con[n-2], con[n-1], t))
			con.pop_back(), n--;
		con.push_back(t), n++;
	}
}
void CDQ(int l, int r, vector<Line> &con) {
	if (l == r) {
		if (dp[l] >= S[l].p)
			con.push_back(Line(dp[l] + S[l].r - S[l].p - (S[l].d+1)*S[l].g, S[l].g));
		return ;
	}
	int mid = (l+r)/2;
	vector<Line> lcon, rcon;
	CDQ(l, mid, lcon);
	merge(l, mid, r, lcon);
	CDQ(mid+1, r, rcon);
	convex(lcon, rcon, con);
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
//		scanf("%d %d %d", &N, &C, &D) == 3 && N
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
		vector<Line> con;
		CDQ(0, N-1, con);
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
