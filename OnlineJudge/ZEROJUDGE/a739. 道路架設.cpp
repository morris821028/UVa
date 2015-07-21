#include <bits/stdc++.h>
using namespace std;
const int MAXV = 2000005;
const int MAXQ = 100005;
const int MAXE = 2000005;
class LCA {
public:
	struct Edge {
    	int v;
    	Edge *next;
	};
	struct QEdge {
		int qid, u;
		QEdge *next;
	};
	Edge edge[MAXE], *adj[MAXV], *arc[MAXV];
	QEdge qedge[MAXQ<<1], *qadj[MAXV], *qarc[MAXV];
	int e, eq, n;
	int parent[MAXV], weight[MAXV], visited[MAXV], LCA[MAXQ];
	void init(int n) {
		e = eq = 0, this->n = n;
		for (int i = 0; i < n; i++)
			adj[i] = NULL, qadj[i] = NULL;
	}
	void addDedge(int x, int y) {
		edge[e].v = y, edge[e].next = adj[x], adj[x] = &edge[e++];
	}
	void addQuery(int x, int y, int qid) {
		qedge[eq].qid = qid, qedge[eq].u = y, qedge[eq].next = qadj[x], qadj[x] = &qedge[eq++];
		qedge[eq].qid = qid, qedge[eq].u = x, qedge[eq].next = qadj[y], qadj[y] = &qedge[eq++];
	}
	void offline(int root) {
		tarjan(root);
	}
private:	
	int findp(int x) {
	    return parent[x] == x ? x : (parent[x] = findp(parent[x]));
	}
	int joint(int x, int y) {
	    x = findp(x), y = findp(y);
	    if(x == y)	return 0;
	    if(weight[x] > weight[y])
	        weight[x] += weight[y], parent[y] = x;
	    else
	        weight[y] += weight[x], parent[x] = y;
	    return 1;
	}
	struct Node {
		int u, p, line;
		Node(int a = 0, int b = 0, int c = 0):
			u(a), p(b), line(c) {}
	};
	void tarjan(int root) {
		for (int i = 0; i < n; i++) 
			arc[i] = adj[i], qarc[i] = qadj[i], visited[i] = 0;
		stack<Node> stk;
		Node u;
		int x, y;
		stk.push(Node(root, -1, 0));
		parent[root] = root;
		while (!stk.empty()) {
			u = stk.top(), stk.pop();
			if (u.line == 0) {
				if (arc[u.u]) {
					y = arc[u.u]->v, arc[u.u] = arc[u.u]->next;
        			stk.push(u);
					parent[y] = y;
        			stk.push(Node(y, u.u, 0));
				} else {
					visited[u.u] = 1;
					u.line++;
					stk.push(u);
				}
			} else {
				if (qarc[u.u]) {
					x = qarc[u.u]->qid, y = qarc[u.u]->u, qarc[u.u] = qarc[u.u]->next;
	        		stk.push(u);
	        		if (visited[y])
	        			LCA[x] = findp(y);
				} else {
					if (u.p != -1)
						parent[findp(u.u)] = u.p;
				}
			}
		}
	}
} lca;
int A[MAXQ], B[MAXQ], dist[MAXV];
long long C[MAXV];
struct Node {
	int u, line;
	Node(int a = 0, int b = 0):
		u(a), line(b) {}
};
void dfs(int root) {
	for (int i = 0; i < lca.n; i++) 
		lca.arc[i] = lca.adj[i];
	stack<Node> stk;
	Node u;
	int x, y;
	dist[0] = 0, C[0] = 0;
	stk.push(Node(root, 0));
	while (!stk.empty()) {
		u = stk.top(), stk.pop();
		if (lca.arc[u.u] != NULL) {
			y = lca.arc[u.u]->v;
			lca.arc[u.u] = lca.arc[u.u]->next;
			stk.push(u);
			dist[y] = dist[u.u]+1;
			C[y] += C[u.u];
			stk.push(Node(y, 0));
		}
	}
}
namespace mLocalStream {
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
		static inline void online_printInt(int x) {
			static char ch[16];
			static int idx;
			idx = 0;
			if (x == 0)	ch[++idx] = 0;
			while (x > 0) ch[++idx] = x % 10, x /= 10;
			while (idx) 
				putchar(ch[idx--]+48);
		}
		~Print() {
			*p = '\0';
			printf("%s", buf);
		}
	} bprint;
}
int main() {
	int N, Q, P, c;
	mLocalStream::ReadInt(&N);
	lca.init(N);
	for (int i = 1; i < N; i++) {
		mLocalStream::ReadInt(&P);
		mLocalStream::ReadInt(&c);
		C[i] = c, P--;
		lca.addDedge(P, i);
	}
	mLocalStream::ReadInt(&Q);
	for (int i = 0; i < Q; i++) {
		mLocalStream::ReadInt(A+i);
		mLocalStream::ReadInt(B+i);
		A[i]--, B[i]--;
		lca.addQuery(A[i], B[i], i);
	}
	dfs(0);
	lca.offline(0);
	int lazy = 0;
	long long d1, d2;
	for (int i = 0; i < Q; i++) {
		if (A[i] == B[i] || lca.LCA[i] != A[i])
			lazy++;
		else {
			d1 = dist[A[i]] + dist[B[i]] - 2*dist[lca.LCA[i]];
			d2 = C[A[i]] + C[B[i]] - 2*C[lca.LCA[i]];
			printf("%lld\n", d1*lazy + d2);
		}
	}
	return 0;
}
/*
4
1 3
1 7
2 5
3
1 4
2 3
1 4
*/

