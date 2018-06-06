#include <bits/stdc++.h> 
using namespace std;
/* disjoint set + sweep line algorithm, O(nm log m) */
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
} e[MAXM], se[MAXM];
struct ISMQ {
	int lIdx, x;
	int value[MAXM], parent[MAXM];
	int weight[MAXM], leader[MAXM];
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
	    for (int32_t *v = leader + lIdx; lIdx >= 0 && value[*v] >= V; v--, lIdx--) {
	        if (weight[lIdx] > maxW)
	            sum = maxW = weight[lIdx], u = *v;
	        else if (weight[lIdx] == maxW)
	            sum ++;
	    }
	    for (int32_t *v = leader + lIdx+1, *vend = leader + rIdx+1; v != vend; v++)
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
			static set<pair<int, int>> S;
			
			memset(C, 0, sizeof(C[0])*m);
			for (int j = 0; j < m; j++) {
				int l = max(j-f[i-1][j], 0);
				int r = min(j+f[i-1][j], m-1);
				e[j] = Event(l, r, dp[j]);
				C[l]++;
			}
			for (int j = 1; j < m; j++)
				C[j] += C[j-1];
			for (int j = m-1; j >= 0; j--)
				se[--C[e[j].l]] = e[j];
		
			S.clear();
			for (int j = 0, k = 0; j < m; j++) {
				while (k < m && se[k].l <= j)
					S.insert({se[k].v, se[k].r}), k++;
				while (!S.empty() && S.begin()->second < j)
					S.erase(S.begin());
				if (S.empty())
					A[j] = INF;
				else
					A[j] = S.begin()->first;
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
