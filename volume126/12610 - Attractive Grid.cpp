#include <bits/stdc++.h> 
using namespace std;
struct Event {
	int r, c, color, t;
	Event(int r=0, int c=0, int color=0, int t=0):
		r(r), c(c), color(color), t(t) {}
	bool operator<(const Event &e) const {
		if (c != e.c)
			return c < e.c;
		return (t == 1) ? (r > e.r) : (r < e.r);
	}
};
const int MAXCOLOR = 100005;
const int MAXEVENT = 100005;
multiset<int, greater<int>> C[MAXCOLOR];	// max-heap
int M, E, L;
Event evt[MAXEVENT*2];
int dx[MAXEVENT];
struct SegmentTree {
	uint16_t tree[(131072)<<1];	// HACK: short type
	int M, tot;	// use tot instead of tree[1]
	void init(int n) {	// [1...n]
		for (M = 1; M < n+1; M <<= 1);
		memset(tree, 0, sizeof(tree[0])*(2*M));
		tot = 0;
	}
	void add(int pos, int val) {
		pos = pos + M, tot += val;
		while (pos)
			tree[pos] += val, pos >>= 1;
	}
	int r_index(int sum) {
		if (tot < sum)
			return 0;
		int s = 1, tar = tot-sum;
		while (s < M) {
			if (tree[s<<1] > tar)
				s = s<<1;
			else
				tar -= tree[s<<1], s = s<<1|1;
		}
		return s-M;
	}
} tree;
int64_t solve() {
	if (L == 0)
		return (int64_t) M*M;

	dx[E] = 0;
	sort(dx, dx+E+1);
	int dx_n = unique(dx, dx+E+1)-dx;
	
	sort(evt, evt+2*E);
	for (int i = 0; i < 2*E; i++) {
		auto &e = evt[i];
		e.r = (int) (lower_bound(dx, dx+dx_n, e.r) - dx);
	}
	tree.init(dx_n);
	int64_t ret = 0;
	for (int i = 0; i < 2*E; ) {
		int cur_y = evt[i].c;
		while (i < 2*E && evt[i].c == cur_y) {
			int color = evt[i].color, r = evt[i].r, t = evt[i].t;
			if (t == 1) {
				if (C[color].begin() == C[color].end() || *C[color].begin() < r) {
					if (C[color].begin() != C[color].end()) {
					// -- C[color].begin()
						tree.add(*C[color].begin(), -1);
					}
					// ++ r
					tree.add(r, 1);
				}
				C[color].insert(r);
			} else {
				auto it = C[color].find(r);
				if (C[color].begin() == it) {
					// --r
					tree.add(r, -1);
					C[color].erase(it);
					if (C[color].begin() != C[color].end()) {
						// ++C[color].begin()
						tree.add(*C[color].begin(), 1);
					}
				} else {
					C[color].erase(it);
				}
			} 
			i++;
		}

		if (i == 2*E)
			continue;
		int64_t dy = evt[i].c - cur_y;
		ret += dy * dx[tree.r_index(L)];
	}
	return ret;
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
	int testcase,cases = 0;
//	scanf("%d", &testcase);
	ReadInt(&testcase);
	while (testcase--) {
//		scanf("%d %d %d", &M, &E, &L);
		ReadInt(&M), ReadInt(&E), ReadInt(&L);
		for (int i = 0; i < E; i++) {
			int r, c1, c2, c;
//			scanf("%d %d %d %d", &r, &c1, &c2, &c);
			ReadInt(&r), ReadInt(&c1), ReadInt(&c2), ReadInt(&c);
			evt[i] = Event(r, c1-1, c, 1);
			evt[i+E] = Event(r, c2, c, -1);
			dx[i] = r;
		}

		int64_t ret = solve();
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
2
10  4  1
3  2  6  1
4  2  5  1
5  4  8  2
3  7  10  3

10  4  2
3  2  6  1
4  2  5  1
5  4  8  2
3  7  10  3
*/

