#include <stdio.h>
#include <string.h> 
#define MAXN 32767
#define MAXM 131072
struct Node {
    int x, y, next;
};
struct Node edge[MAXM];
int e, head[MAXN];
void addEdge(int x, int y) {
    edge[e].x = x, edge[e].y = y;
    edge[e].next = head[x], head[x] = e++;
}

int wa[MAXN];
int dfs(int u) {
	wa[u] = 1;
	int i;
	for (i = head[u]; i != -1; i = edge[i].next) {
		int v = edge[i].y;
		if (!wa[v])	dfs(v);
	}
}
int main() {
	int n, m, l, q;
	int x, y, i;
	while (scanf("%d %d %d %d", &n, &m, &l, &q) == 4) {
		e = 0;
		memset(head, -1, sizeof(head));
		memset(wa, 0, sizeof(wa));
		for (i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			addEdge(x, y);
		}
		for (i = 0; i < l; i++) {
			scanf("%d", &x);
			dfs(x);
		}
		for (i = 0; i < q; i++) {
			scanf("%d", &x);
			puts(!wa[x] ? "YA~~" : "TUIHUOOOOOO");
		}
	}
	return 0;
}

