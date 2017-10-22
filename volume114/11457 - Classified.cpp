#include <bits/stdc++.h> 
using namespace std;
// paper: LCA Queries in Directed Acyclic Graphs
const int MAXV = 10005;
const int MAXE = 10005;
struct Node {
    int to, next;
} edge[MAXE];
int e, head[MAXV];
void addEdge(int x, int y) {
    edge[e].to = y;
    edge[e].next = head[x], head[x] = e++;
}

int visited[MAXV];
int16_t dist[MAXV][MAXV];
void bfs(int u, int L) {
	visited[u] = 1;
	memset(dist[u]+1, 0x3f, sizeof(dist[0][0])*L);
	static int Q[MAXV][2], used[MAXV] = {}, cases = 0;
	int Qt = 0, Qidx = 0;
	int16_t *R = dist[u];
	Q[Qt][0] = u, Q[Qt][1] = 0, Qt++;
	cases++;
	while (Qidx < Qt) {
		int u = Q[Qidx][0], d = Q[Qidx][1];
		R[u] = d;
		Qidx++;
		for (int v = head[u]; v != -1; v = edge[v].next) {
			int to = edge[v].to;
			if (used[to] != cases) {
				used[to] = cases;
				Q[Qt][0] = to, Q[Qt][1] = d+1;
				Qt++;
			}
		}
	}
}
int main() {
	int testcase;
	int L, R, U, D, A;
	static int usr[MAXV], doc[MAXV];
	scanf("%d", &testcase);
	while (testcase--) {
		// layer, rule, user, document, action
		scanf("%d %d %d %d %d", &L, &R, &U, &D, &A);
		
		e = 0;
		memset(head, -1, sizeof(head));
		for (int i = 0; i < R; i++) {
			int x, y;
			scanf("%d %d", &x, &y);	// x->y
			// store y->x
			addEdge(y, x);
		}
		
		for (int i = 1; i <= U; i++)
			scanf("%d", &usr[i]);
		for (int i = 1; i <= D; i++)
			scanf("%d", &doc[i]);
		
		memset(visited, 0, sizeof(visited));
		for (int it = 0; it < A; it++) {
			static char cmd[16];
			int x, y, lx, ly;
			scanf("%d %s %d", &x, &cmd, &y);
			lx = usr[x], ly = doc[y];
			if (visited[lx] == 0)
				bfs(lx, L);
			if (visited[ly] == 0)
				bfs(ly, L);
				
			const int16_t *l = dist[lx], *r = dist[ly];
			
			int ret = INT_MAX, ret_v = -1;
			for (int i = 1; i <= L; i++) {
				if (l[i] + r[i] < ret)
					ret = l[i] + r[i], ret_v = i;
			}
			
			if (cmd[0] == 'r') { // read
				usr[x] = ret_v;
			} else {	// write
				doc[y] = ret_v;
			}
			
			printf("%d\n", ret_v);
		}
	}
	return 0;
}
/*
1
9 11 2 3 5
6 9
2 6
9 4
7 5
3 8
7 2
5 3
8 4
5 1
6 1
1 8
4
2
5
9
8
1 reads 3
1 writes 2
2 reads 2
1 reads 1
2 writes 1
*/
