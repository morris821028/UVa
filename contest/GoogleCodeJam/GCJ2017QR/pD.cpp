#include <bits/stdc++.h>
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
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);
		
		g.Init(6*n+5);
		static int mm[800][800];
		static int mmPos[800][800][2];
		int ret = 0;
		memset(mm, 0, sizeof(mm));
		int source = 6*n+1, sink = 6*n+2;
		int board[128][128] = {};
		int board_t[128][128] = {};
		char board_s[128][128] = {};
		int ban[800] = {};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				mm[i][j+n] = 1;
				mm[(i+j)+2*n][(i-j+n-1)+4*n] = 1;
				mmPos[i][j+n][0] = i;
				mmPos[i][j+n][1] = j;
				mmPos[(i+j)+2*n][(i-j+n-1)+4*n][0] = i;
				mmPos[(i+j)+2*n][(i-j+n-1)+4*n][1] = j;
			}
		}
		for (int i = 0; i < m; i++) {
			char s[16];
			int x, y;
			scanf("%s %d %d", s, &x, &y);
			x--, y--;
			board_s[x][y] = s[0];
			if (s[0] == 'o') {
				ret += 2, board[x][y] = 2;
				ban[x] = 1, ban[y+n] = 1;
				ban[(x+y)+(2*n)] = 1;
				ban[(x-y+n-1)+4*n] = 1;
			} else if (s[0] == '+') {
				ret += 1, board[x][y] = 1;
				ban[(x+y)+(2*n)] = 1;
				ban[(x-y+n-1)+4*n] = 1;
//				printf("%d %d\n", x+y+2*n, x-y+n-1+4*n);
			} else if (s[0] == 'x') {
				ret += 1, board[x][y] = 1;
				ban[x] = 1, ban[y+n] = 1;
			}
		}
		memcpy(board_t, board, sizeof(board));
		
		for (int i = 0; i < n; i++)
			g.Addedge(source, i, 1);
		for (int i = 2*n; i < 4*n; i++)
			g.Addedge(source, i, 1);
		for (int i = n; i < 2*n; i++)
			g.Addedge(i, sink, 1);
		for (int i = 4*n; i < 6*n; i++)
			g.Addedge(i, sink, 1);
		
		for (int i = 0; i < n; i++) {
			for (int j = n; j < 2*n; j++) {
				if (ban[i] || ban[j] || !mm[i][j])
					continue;
				g.Addedge(i, j, 1);
			}
		}
		for (int i = 2*n; i < 4*n-1; i++) {
			for (int j = 4*n; j < 6*n-1; j++) {
				if (ban[i] || ban[j] || !mm[i][j])
					continue;
				g.Addedge(i, j, 1);
			}
		}
		
		int flow = g.Maxflow(source, sink);
		
		
		for (int i = 0; i < n; i++) {
			for (Edge *p = g.adj[i]; p != NULL; p = p->next) {
				if (p->v >= n && p->v < 2*n && p->flow == 0) {
					board_t[mmPos[i][p->v][0]][mmPos[i][p->v][1]]++;
//					printf("---- %d %d\n", mmPos[i][p->v][0], mmPos[i][p->v][1]);
					board_s[mmPos[i][p->v][0]][mmPos[i][p->v][1]] = 'x';
				}
			}
		}
		for (int i = 2*n; i < 4*n; i++) {
			for (Edge *p = g.adj[i]; p != NULL; p = p->next) {
				if (p->v >= 4*n && p->v < 6*n && p->flow == 0) {
					board_t[mmPos[i][p->v][0]][mmPos[i][p->v][1]]++;
//					printf("---- %d %d\n", mmPos[i][p->v][0], mmPos[i][p->v][1]);
					board_s[mmPos[i][p->v][0]][mmPos[i][p->v][1]] = '+';
				}
			}
		}
		
		struct DD {
			int x, y;
			char val;
			DD(int x, int y, char val): x(x), y(y), val(val) {}
		};
		vector<DD> V;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (board_t[i][j] != board[i][j]) {
					if (board_t[i][j] == 2)
						V.push_back(DD(i+1, j+1, 'o'));
//						printf("o %d %d\n", i+1, j+1);
					else if (board_t[i][j] == 1)
						V.push_back(DD(i+1, j+1, board_s[i][j]));
//						printf("%c %d %d\n", board_s[i][j], i+1, j+1);
				}
			}
		}
		printf("Case #%d: %d %d\n", ++cases, ret+flow, V.size());
		for (int i = 0; i < V.size(); i++)
			printf("%c %d %d\n", V[i].val, V[i].x, V[i].y);
	}
	return 0;
}
/*
3
2 0
1 1
o 1 1
3 4
+ 2 3
+ 2 1
x 3 1
+ 2 2

	

Case #1: 4 3
o 2 2
+ 2 1
x 1 1
Case #2: 2 0
Case #3: 6 2
o 2 3

*/
