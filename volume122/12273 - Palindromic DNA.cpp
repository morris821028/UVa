#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 10005*4;
const int MAXE = 16777216;


inline int readchar() {
    const int N = 1048576;
    static char buf[N];
    static char *p = buf, *end = buf;
    if (p == end) {
        if((end = buf + fread(buf, 1, N, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int ReadInt(int *x) {
    static char c, neg;
    while ((c = readchar()) < '-')	{ if(c == EOF) return 0;}
    neg = (c == '-') ? -1 : 1;
    *x = (neg == 1) ? c-'0' : 0;
    while ((c = readchar()) >= '0' && c <= '9')
        *x = (*x << 3) + (*x << 1) + c-'0';
    *x *= neg;
    return 1;
}
inline int ReadStr(char *s) {
	static char c;
	while ((c = readchar()) <= ' ')	{if (c == EOF)	return 0;}
	*s = c, s++;
	while ((c = readchar()) > ' ')
		*s = c, s++;
	*s = '\0';
	return 1;
}

class TwoSat {
public:
	struct Edge {
	    int to;
	    Edge *next;
	};
	Edge edge[MAXE], *adj[MAXN];
	int e;
    int n;
	int mark[MAXN], stk[MAXN];
	int stkIdx;
	void addEdge(int u, int v) { // u -> v
		edge[e].to = v;
		edge[e].next = adj[u], adj[u] = &edge[e++];
    }
	int dfs(int u) {
	   	if (mark[u^1])
			return 0;
		if (mark[u])
			return 1;
		mark[u] = 1, stk[stkIdx++] = u;
		for (Edge *p = adj[u]; p; p = p->next) {
			int v = p->to;
			if (!dfs(v))
				return 0;
		}
		return 1;
	}
	int solvable() {
        for (int i = 0; i < n; i++)
            mark[i] = 0;
        for (int i = 0; i < n; i += 2) {
        	if (mark[i] == 0 && mark[i^1] == 0) {
        		stkIdx = 0;
        		if (dfs(i) == 0) {
        			while (stkIdx)
        				mark[stk[--stkIdx]] = 0;
        			if (dfs(i^1) == 0)
        				return false;
				}
			}
		}
		return true;
	}
    void init(int n) {
        this->n = n;
        e = 0;
    	for (int i = 0; i < n; i++)
    	    adj[i] = NULL;
    }
} g;

void cond(int x0, int b0, int x1, int b1) {	// AND (b0(X0) OR b1(X1))
	g.addEdge(x0<<1 | (b0^1), x1<<1|b1);
	g.addEdge(x1<<1 | (b1^1), x0<<1|b0);
}

void cond_same(int x0, int x1) {
	cond(x0, 1, x1, 0);
	cond(x0, 0, x1, 1);
}
void cond_diff(int x0, int x1) {
	cond(x0, 0, x1, 0);
	cond(x0, 1, x1, 1);
}
void set_val(int x, int val) {
	g.addEdge(x<<1|val^1, x<<1|val);
}

int main() {
	int n, m;
	char s[10005];
	
	static char alph[] = "AGTC";
	static char next[] = "GTCA";
	static int malph[128] = {};
	malph['A'] = 0, malph['G'] = 1, malph['T'] = 2, malph['C'] = 3;
	
//	while (scanf("%d %d", &n, &m) == 2 && n) {
	while (ReadInt(&n) == 1 && n) {
		ReadInt(&m);
		ReadStr(s);
//		scanf("%s", s);
		
		g.init(4*n);
		
		// x_i: pos_i changed (true/false)
		// y_i: pos_i up/down (true/false)
		
		// adjacency position
		for (int i = 1; i < n; i++) {
			int x0 = i-1, x1 = i;
			cond(x0, 0, x1, 0);		// AND (NOT(x0) OR NOT(x1))
		}
		
		for (int it = 0; it < m; it++) {
			int l;
			static int A[10005];
//			scanf("%d:", &l);
			ReadInt(&l);
			for (int i = 0; i < l; i++)
//				scanf("%d", &A[i]);
				ReadInt(&A[i]);
			for (int i = 0, j = l-1; i < j; i++, j--) {
				int a = A[i], b = A[j];
				int d = abs(malph[s[a]] - malph[s[b]]);
				d = min(d, 4-d);

				if (d == 0) {
					cond_same(a, b);		// x_a == x_b
					cond_same(a+n, b+n);	// y_a == y_b
				} else if (d == 1) {
					cond_diff(a, b);		// x_a != x_b
					if (s[b] != next[malph[s[a]]]) {
						cond(a, 1, b+n, 1);
						cond(b, 1, a+n, 0);
					} else {
						cond(a, 1, b+n, 0);
						cond(b, 1, a+n, 1);
					}
				} else if (d == 2) {
					set_val(a, 1);			// x_a = true
					set_val(b, 1);			// x_b = true
					cond_diff(a+n, b+n);	// y_a != y_b
				} else {
					assert(false);
				}
			}
		}
		
		int ret = g.solvable();
		puts(ret ? "YES" : "NO");
	}	
	return 0;
}
/*
5 3
AGTAT
2: 1 4
2: 0 1
3: 0 2 4

5 3
CATGC
0:
2: 0 3
2: 3 4

0 0
*/
