#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAXQ = 50005;
const int64_t INF = 1LL<<60;

struct Pt {
	int64_t x, y;
	int type;
	Pt() {}
	Pt(int x, int y, int t):x(x), y(y), type(t) {}
	bool operator==(const Pt &p) const {
		return x == p.x && y == p.y && type == p.type;
	}
	bool operator<(const Pt &p) const {
		if (x != p.x)	return x < p.x;
		if (y != p.y)	return y < p.y;
		return type < p.type;
	}
};
static bool cmpX(const Pt &x, const Pt &y) {
	return x.x < y.x;
}
static bool cmpY(const Pt &x, const Pt &y) {
	return x.y < y.y;
}

int treeN;
int64_t treeL[MAXN], treeR[MAXN];
void init_bit(int n) {
	for (int i = 0; i <= n; i++)
		treeL[i] = -INF;
	for (int i = 0; i <= n; i++)
		treeR[i] = -INF;
	treeN = n;
}
int64_t query(int x, int type) {
	int64_t ret = -INF;
	if (type == 0) {
		while (x > 0) {
			ret = max(ret, treeL[x]);
			x -= x&(-x);
		}
	} else {
		while (x <= treeN) {
			ret = max(ret, treeR[x]);
			x += x&(-x);
		}
	}
	return ret;
}
void add(int x, int64_t val, int type) {
	if (type == 0) {
		while (x <= treeN) {
			treeL[x] = max(treeL[x], val);
			x += x&(-x);
		}
	} else {
		while (x > 0) {
			treeR[x] = max(treeR[x], val);
			x -= x&(-x);
		} 
	}
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
	int n, m;
	int x, y;
	int cases = 0;
	static int64_t ret[MAXQ];
//	while (scanf("%d", &n) == 1 && n >= 0) {
	while (ReadInt(&n) && n >= 0) {
		if (cases++)
			puts("");

		vector<Pt> A;
		for (int i = 0; i < n; i++) {
//			scanf("%d %d", &x, &y);
			ReadInt(&x), ReadInt(&y);
			A.emplace_back(Pt(x, y, -1));
		}

//		scanf("%d", &m);
		ReadInt(&m);
		for (int i = 0; i < m; i++) {
//			scanf("%d %d", &x, &y);
			ReadInt(&x), ReadInt(&y);
			A.emplace_back(Pt(x, y, i));
			ret[i] = INF;
		}
		
		vector<int64_t> Y;
		for (int i = 0; i < A.size(); i++)
			Y.emplace_back(A[i].y);
		sort(Y.begin(), Y.end());
		Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
			
		sort(A.begin(), A.end(), cmpX);
		init_bit(Y.size());
		for (int i = 0; i < A.size(); i++) {
			int vy = lower_bound(Y.begin(), Y.end(), A[i].y) - Y.begin() + 1;
			if (A[i].type >= 0) {
				int64_t mn = ret[A[i].type];
				mn = min(mn, A[i].x+A[i].y-query(vy, 0));
				mn = min(mn, A[i].x-A[i].y-query(vy, 1));
				ret[A[i].type] = mn;
			} else {
				add(vy, A[i].x+A[i].y, 0);
				add(vy, A[i].x-A[i].y, 1);
			}
		}
		init_bit(Y.size());
		for (int i = A.size()-1; i >= 0; i--) {
			int vy = lower_bound(Y.begin(), Y.end(), A[i].y) - Y.begin() + 1;
			if (A[i].type >= 0) {
				int64_t mn = ret[A[i].type];
				mn = min(mn, -A[i].x+A[i].y-query(vy, 0));
				mn = min(mn, -A[i].x-A[i].y-query(vy, 1));
				ret[A[i].type] = mn;
			} else {
				add(vy, -A[i].x+A[i].y, 0);
				add(vy, -A[i].x-A[i].y, 1);
			}
		}

		for (int i = 0; i < m; i++)
			printf("%u\n", ret[i]);
	} 
	return 0;
}
/*
2
2 3
3 4
2
1 1
3 4
2
1 1
9 9
4
4 5
6 5
2 5
3 4
-1
*/
