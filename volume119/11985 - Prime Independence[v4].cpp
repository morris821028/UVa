#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <assert.h>
#include <set>
using namespace std;

const int MAXV = 40010;
const int MAXE = MAXV * 200 * 2;
const int INF = 1<<29;
typedef struct Edge {
    int v, cap, flow;
    Edge *next, *re;
} Edge;
class MaxFlow {
    public:
    Edge edge[MAXE], *adj[MAXV], *pre[MAXV], *arc[MAXV];
    int e, n, level[MAXV], lvCnt[MAXV], Q[MAXV];
    void Init(int x) {
        n = x, e = 0;
        for (int i = 0; i < n; ++i) adj[i] = NULL;
    }
    void Addedge(int x, int y, int flow){
        edge[e].v = y, edge[e].cap = flow, edge[e].next = adj[x];
        edge[e].re = &edge[e+1], adj[x] = &edge[e++];
        edge[e].v = x, edge[e].cap = 0, edge[e].next = adj[y];
        edge[e].re = &edge[e-1], adj[y] = &edge[e++];
    }
    void Bfs(int v){
        int front = 0, rear = 0, r = 0, dis = 0;
        for (int i = 0; i < n; ++i) level[i] = n, lvCnt[i] = 0;
        level[v] = 0, ++lvCnt[0];
        Q[rear++] = v;
        while (front != rear){
            if (front == r) ++dis, r = rear;
            v = Q[front++];
            for (Edge *i = adj[v]; i != NULL; i = i->next) {
                int t = i->v;
                if (level[t] == n) level[t] = dis, Q[rear++] = t, ++lvCnt[dis];
            }
        }
    }
    int Maxflow(int s, int t){
        int ret = 0, i, j;
        Bfs(t);
        for (i = 0; i < n; ++i) pre[i] = NULL, arc[i] = adj[i];
        for (i = 0; i < e; ++i) edge[i].flow = edge[i].cap;
        i = s;
        while (level[s] < n){
            while (arc[i] && (level[i] != level[arc[i]->v]+1 || !arc[i]->flow)) 
				arc[i] = arc[i]->next;
            if (arc[i]){
                j = arc[i]->v;
                pre[j] = arc[i];
                i = j;
                if (i == t){
                    int update = INF;
                    for (Edge *p = pre[t]; p != NULL; p = pre[p->re->v])
                        if (update > p->flow) update = p->flow;
                    ret += update;
                    for (Edge *p = pre[t]; p != NULL; p = pre[p->re->v])
                        p->flow -= update, p->re->flow += update;
                    i = s;
                }
            }
            else{
                int depth = n-1;
                for (Edge *p = adj[i]; p != NULL; p = p->next)
                    if (p->flow && depth > level[p->v]) depth = level[p->v];
                if (--lvCnt[level[i]] == 0) return ret;
                level[i] = depth+1;
                ++lvCnt[level[i]];
                arc[i] = adj[i];
                if (i != s) i = pre[i]->re->v;
            }
        }
        return ret;
    }
} g;

#define MAXL (500000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[100000], Pt = 0;
vector<int> pfactor[524288];
int A[MAXV], RE[524288], XY[524288];
void sieve() {
	register int i, j, k;
	SET(1);
	int n = 500000;
	for(i = 2; i <= n; i++) {
		if(!GET(i)) {
			XY[i] = 1;
//			for(k = n/i, j = i*k; k >= i; k--, j -= i)
//				SET(j);
			for (j = i+i; j <= n; j += i)
				SET(j), XY[j] = XY[j/i] + 1, pfactor[j].push_back(i);
			pfactor[i].push_back(i);
			P[Pt++] = i;
		}
	}
}
int main() {
	sieve();
	int testcase, cases = 0;
	int n, x;
	scanf("%d", &testcase);
	while (testcase--) {
   		scanf("%d", &n);
   		memset(RE, -1, sizeof(RE));
   		for (int i = 0; i < n; i++) {
   			scanf("%d", &A[i]);
   			RE[A[i]] = i;
   		}
   		g.Init(n + 2);
   		int source = n, sink = n + 1;
   		for (int i = 0; i < n; i++) {
   			if (XY[A[i]]&1)
   				g.Addedge(source, i, 1);
   			else
   				g.Addedge(i, sink, 1);
   			for (int j = 0; j < pfactor[A[i]].size(); j++) {
   				int y = A[i] / pfactor[A[i]][j];
   				if (RE[y] != -1) {
   					if (XY[y]&1)
   						g.Addedge(RE[y], i, 1);
   					else
   						g.Addedge(i, RE[y], 1);
   				}
   			}
   		}
   		printf("Case %d: %d\n", ++cases, n - g.Maxflow(source, sink));
   	}
    return 0;
}
/*
3
5
2 4 8 16 32
5
2 3 4 6 9
3
1 2 3

1000
3
7 35 105
*/

