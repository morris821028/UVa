#include <bits/stdc++.h>
using namespace std;

const int MAXN = 4096;
const int MAXE = 524288;
class SCC {
public:
	struct Edge {
	    int to;
	    Edge *next;
	};
	Edge edge[MAXE], *adj[MAXN];
	int e = 0;
    int n;
    // <SCC begin>
    int vfind[MAXN], findIdx;
    int stk[MAXN], stkIdx;
    int in_stk[MAXN], visited[MAXN];
    int contract[MAXN];
    int scc_cnt;
    // <SCC end>
    int scc(int u) {
        in_stk[u] = visited[u] = 1;
        stk[++stkIdx] = u, vfind[u] = ++findIdx;
        int mn = vfind[u], v;
        for(Edge *p = adj[u]; p != NULL; p = p->next) {
        	v = p->to;
            if(!visited[v])
                mn = min(mn, scc(v));
            if(in_stk[v])
                mn = min(mn, vfind[v]);
        }
        if(mn == vfind[u]) {
            do {
                in_stk[stk[stkIdx]] = 0;
                contract[stk[stkIdx]] = scc_cnt;
            } while(stk[stkIdx--] != u);
            scc_cnt++;
        }
        return mn;
    }
    void addEdge(int u, int v) { // u -> v
        edge[e].to = v;
    	edge[e].next = adj[u], adj[u] = &edge[e++];
    }
    void solve() {
        for (int i = 0; i < n; i++)
            visited[i] = in_stk[i] = 0;
        scc_cnt = 0;
        for (int i = 0; i < n; i++) {
        	if (visited[i])	continue;
        	stkIdx = findIdx = 0;
        	scc(i);
        }
    }
    void init(int n) {
        this->n = n;
		e = 0;
		for (int i = 0; i <= n; i++)
			adj[i] = NULL;
    }
} g;

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

class Print {
public:
    static const int N = 1048576;
    char buf[N], *p, *end;
    Print() {
        p = buf, end = buf + N - 1;
    }
    void printInt(int x, char padding) {
        static char stk[16];
        int idx = 0;
        stk[idx++] = padding;
        if (!x)	
            stk[idx++] = '0';
        while (x)
            stk[idx++] = x%10 + '0', x /= 10;
        while (idx) {
            if (p == end) {
                *p = '\0';
                printf("%s", buf), p = buf;
            }
            *p = stk[--idx], p++;
        }
    }
    ~Print() {
        *p = '\0';
        printf("%s", buf);
    }
} bprint;

int main() {
	int n, m, x;
//	while (scanf("%d", &n) == 1) {
	while (ReadInt(&n) == 1) {
		g.init(2*n);
		for (int i = 0; i < n; i++) {
//			scanf("%d", &m);
			ReadInt(&m);
			for (int j = 0; j < m; j++) {
//				scanf("%d", &x), x--;
				ReadInt(&x), x--;
				g.addEdge(i, x+n);
			}
		}

		for (int i = 0; i < n; i++) {
//			scanf("%d", &x), x--;
			ReadInt(&x), x--;
			g.addEdge(x+n, i);
		}

		g.solve();

		for (int i = 0; i < n; i++) {
			static int arr[MAXN];
			int arrIdx = 0;
			for (SCC::Edge *p = g.adj[i]; p != NULL; p = p->next) {
				if (g.contract[i] == g.contract[p->to])
					arr[arrIdx++] = p->to;
			}
//			printf("%d", arrIdx);
			bprint.printInt(arrIdx, ' ');
			for (int j = 0; j < arrIdx; j++) {
				int v = arr[j]-n+1;
				bprint.printInt(v, j != arrIdx-1 ? ' ' : '\n');
//				printf(" %d", v);
			}
//			puts("");
		}
	}
	return 0;
}
/*
4
2 1 2
2 1 2
2 2 3
2 3 4
1 2 3 4
*/
