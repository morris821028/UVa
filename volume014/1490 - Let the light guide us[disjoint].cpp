#include <bits/stdc++.h> 
using namespace std;
/* disjoint set + radix sort, O(nm alpha(m)) */
/** If someone implements drawer in O(m), last part of disjoint query for 
	incremental suffix minimum query will be in O(m) in my paper.
	Totally, this problem is in O(nm).
	*/
const int MAXN = 105;
const int MAXM = 5005;
int f[MAXN][MAXM], t[MAXN][MAXM];
struct Event {
	int l, r, v;
	Event() {}
	Event(int l, int r, int v) {
		this->l = l, this->r = r;
		this->v = v;
	}
	bool operator<(const Event &e) const {
		return v < e.v;
	}
} e[MAXM], se[MAXM];
struct ISMQ {
	int lIdx, x;
	int value[MAXM];
	int16_t parent[MAXM];
	int16_t weight[MAXM], leader[MAXM];
	int findp(int x) {
	    return parent[x] == x ? x : (parent[x] = findp(parent[x]));
	}
	void init_ISMQ(int N) {
	    x = -1, lIdx = -1;
	}
	void append_ISMQ(int V) {
	    ++x;
	    int maxW = 1, u = x, sum = 1;
	    int rIdx = lIdx;
	    for (int16_t *v = leader + lIdx; lIdx >= 0 && value[*v] >= V; v--, lIdx--) {
	        if (weight[lIdx] > maxW)
	            sum = maxW = weight[lIdx], u = *v;
	        else if (weight[lIdx] == maxW)
	            sum ++;
	    }
	    for (int16_t *v = leader + lIdx+1, *vend = leader + rIdx+1; v != vend; v++)
	        parent[*v] = u;
	    parent[x] = u;
	    ++lIdx;
	    value[u] = V;
	    leader[lIdx] = u;
	    weight[lIdx] = sum;
	}
	int query_ISMQ(int L) {
		if (L > x)
			return 0x3f3f3f3f;
	    return value[findp(L)];
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
void _radix_sort(Event *A, int n) {
	static Event _tmp[MAXM];
	const int CHUNK = 256;
	static int C[CHUNK];
	Event *B = _tmp, *T;
    for (int x = 0; x < 4; x++) {
        const int d = x*8;
        memset(C, 0, sizeof(C));
        for (int i = 0; i < n; i++)
			C[(A[i].v>>d)&(CHUNK-1)]++;
        for (int i = 1; i < CHUNK; i++)
			C[i] += C[i-1];
        for (int i = n-1; i >= 0; i--)
			B[--C[(A[i].v>>d)&(CHUNK-1)]] = A[i];
        T = A, A = B, B = T;
    }
}

struct Drawer {
	int16_t parent[MAXM];
	int16_t weight[MAXM];
	int16_t right[MAXM];
	void init(int m) {
		for (int j = 0; j <= m; j++)
			parent[j] = j, right[j] = j, weight[j] = 1;
	}
	int findp(int x) {
	    return parent[x] == x ? x : (parent[x] = findp(parent[x]));
	}
	int next(int x) {
		return right[findp(x)];
	}
	int joint(int l, int r) {
		l = findp(l), r = findp(r);
		if (weight[l] < weight[r])
			weight[r] += weight[l], parent[l] = r;
		else
			weight[l] += weight[r], parent[r] = l, right[l] = right[r];
	}
} drawer;


int main() {
	int n, m;
//	while (scanf("%d %d", &n, &m) == 2 && n) {
	while (ReadInt(&n) && n) {
		ReadInt(&m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
//				scanf("%d", &t[i][j]);
				ReadInt(&t[i][j]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
//				scanf("%d", &f[i][j]);
				ReadInt(&f[i][j]);
		}
		static const int INF = 0x3f3f3f3f;
		static int dp[MAXM], A[MAXM];
		for (int i = 0; i < m; i++)
			dp[i] = t[0][i];
		for (int i = 1; i < n; i++) {
			static int C[MAXM];
			int tm = 0;
			for (int j = 0; j < m; j++) {
				if (dp[j] >= INF)
					continue;
				int l = max(j-f[i-1][j], 0);
				int r = min(j+f[i-1][j], m-1);
				e[tm++] = Event(l, r, dp[j]);
			}
			_radix_sort(e, tm);
			drawer.init(m);
			for (int j = 0; j < tm; j++) {
				int l = e[j].l, r = e[j].r, v = e[j].v;
				int f = drawer.next(r+1);
				l = drawer.next(l);
				while (l <= r) {
					A[l] = v;
					drawer.joint(l, f);
					l = drawer.next(l+1);
				}
			}
				
			memset(C, 0, sizeof(C[0])*m);
			for (int j = 0; j < m; j++) {
				int l = max(j-f[i][j], 0);
				int r = min(j+f[i][j], m-1);
				e[j] = Event(l, r, j);
				C[r]++;
			}
			for (int j = 1; j < m; j++)
				C[j] += C[j-1];
			for (int j = m-1; j >= 0; j--)
				se[--C[e[j].r]] = e[j];
			
			tool.init_ISMQ(m);
			for (int j = 0, a = 0; j < m; j++) {
				while (a <= se[j].r) {
					tool.append_ISMQ(A[a]);
					a++;
				}
				dp[se[j].v] = t[i][se[j].v] + tool.query_ISMQ(se[j].l);
			}
		}
		
		int ret = INF;
		for (int i = 0; i < m; i++)
			ret = min(ret, dp[i]);
		printf("%d\n", ret);
	}
	return 0;
}
/*
3  5
9  5  3  8  7
8  2  6  8  9
1  9  7  8  6

0  1  0  1  2
1  0  2  1  1
0  2  1  0  2
0  0
*/
