// Hall's marriage theorem, bipartite graph matching, maxflow
// for all subset X sat. |X| <= |Neighborhood(X)| = |Y|
// 
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
int main() {
	int testcase;
	int n, x, y;
	char s[128][128];
	
	scanf("%d", &testcase);
	while (testcase--) {
		
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", s[i]);
			
		vector<int> bigraph[128];
		int row_deg[128] = {}, col_deg[128] = {};
		int place_color[128][128];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (s[i][j] == '*') {
					row_deg[i]++, col_deg[j]++;
					bigraph[i].push_back(j);
				}					
			}
		}
		
		int mx_colors = 0;
		for (int i = 0; i < n; i++) {
			mx_colors = max(mx_colors, row_deg[i]);
			mx_colors = max(mx_colors, col_deg[i]);
		}
		
		// increase edge, make perfect matching
		for (int i = 0; i < n; i++) {
			if (row_deg[i] < mx_colors) {
				for (int j = 0; j < n; j++) {
					while (row_deg[i] < mx_colors && col_deg[j] < mx_colors) {
						row_deg[i]++, col_deg[j]++;
						bigraph[i].push_back(j);
					}
				}
			}
		}
		
		// bipartite graph matching
		for (int color = 0; color < mx_colors; color++) {
			g.Init(2 * n + 2);
			int source = 2 * n, sink = 2 * n + 1;
			for (int i = 0; i < n; i++) {
				g.Addedge(source, i, 1), g.Addedge(i + n, sink, 1);
				for (int j = 0; j < bigraph[i].size(); j++)
					g.Addedge(i, bigraph[i][j] + n, 1);
			}
			
			int matching = g.Maxflow(source, sink);
			assert(matching == n); // perfect matching
			// make sure, matching pair won't collision.
			for (int i = 0; i < n; i++) {
				for (Edge *p = g.adj[i]; p != NULL; p = p->next) {
					int x = i, y = p->v, flow = p->flow;
					if (flow == 0 && y - n >= 0 && y - n < n) {
						// match x - (y - n) in bipartite graph
						int r = x, c = y - n;
						if (s[r][c] == '*')
							place_color[r][c] = color;
						// remove edge
						bigraph[r].erase(find(bigraph[r].begin(), bigraph[r].end(), c));
					}
				}
			}
		}
		
		for (int i = 0; i < n; i++)
			assert(bigraph[i].size() == 0);
		
		printf("%d\n", mx_colors);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (s[i][j] == '*')	printf("%d", place_color[i][j] + 1);
				else				printf("%d", 0);
				printf("%c", j == n-1 ? '\n' : ' ');
			}
		}
	}
	return 0;
}
/*
9999

4
****
****
****
****

4
***.
.***
.**.
....

4
****
.*.*
..**
...*

4
*...
.*..
..*.
...*

4
*...
.*..
..*.
..*.

2
*.
**

4
*.*.
*.*.
***.
..**
*/
