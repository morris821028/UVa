#include <bits/stdc++.h>
using namespace std;

const int MAXV = 40010;
const int MAXE = MAXV * 200 * 2;
const long long LLINF = 1LL<<62;
typedef struct Edge {
    int v;
    long long cap, flow;
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
    void Addedge(int x, int y, long long flow){
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
    long long Maxflow(int s, int t){
        long long ret = 0;
        int i, j;
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
                    long long update = LLINF;
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

int mtime(int t) {
	return t/100 * 60 + t%100;
}

int main() {
	int n, m, ed_t;
	char st_s[16], ed_s[16];
	while (scanf("%d", &n) == 1) {
		scanf("%s %s", st_s, ed_s);
		scanf("%d", &ed_t);
		ed_t = mtime(ed_t);
		
		scanf("%d", &m);
		map<string, int> R;
		int I[8192][5];
		for (int i = 1, size = 0; i <= m; i++) {
			char s1[16], s2[16];
			int cap, st, ed;
			scanf("%s %s %d %d %d", s1, s2, &cap, &st, &ed);
			int &u = R[s1], &v = R[s2];
			if (u == 0)	u = ++size;
			if (v == 0)	v = ++size;
			I[i][0] = u, I[i][1] = v;
			I[i][2] = cap;
			I[i][3] = mtime(st);
			I[i][4] = mtime(ed);
		}
		int &st = R[st_s], &ed = R[ed_s];
		if (st == 0 || ed == 0) {
			puts("0");
			continue;
		}
		
		g.Init(2+m*2);
		int source = 0, sink = 1;
		for (int i = 1; i <= m; i++) {
			g.Addedge(i*2, i*2+1, I[i][2]);
			if (I[i][0] == st)
				g.Addedge(source, i*2, LLINF);
			if (I[i][1] == ed && I[i][4] <= ed_t)
				g.Addedge(i*2+1, sink, LLINF);
			for (int j = 1; j <= m; j++) {
				if (i == j)
					continue;
				if (I[i][1] == I[j][0] && I[i][4]+30 <= I[j][3])
					g.Addedge(i*2+1, j*2, LLINF);
			}
		}
		
		int ret = g.Maxflow(source, sink);
		printf("%d\n", ret);
	}
	return 0;
}
/*
4
lisbon
berlin
1500
9
lisbon london 6 1000 1100
london lisbon 6 1130 1230
lisbon paris 5 1000 1100
paris lisbon 4 1130 1230
london paris 1 1130 1300
london berlin 2 1340 1510
berlin london 2 1300 1430
paris berlin 10 1330 1500
berlin paris 9 1300 1430
*/
