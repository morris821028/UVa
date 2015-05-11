#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;
const int MAXN = 131072;
struct Node {
	Node *lson, *rson;
	int label, h;
} nodes[MAXN];

int used[MAXN], used2[MAXN], dp[MAXN];
int getHeight(Node *u) {
	if (u == NULL)	
		return 0;
	if (used[u->label])	
		return u->h;
	used[u->label] = 1;
	u->h = max(getHeight(u->lson), getHeight(u->rson)) + 1;
	return u->h;
}
/*
	lh: u become root, max_depth by passing u >> u->parent >> u->parent.lson ...
	rh: u become root, max_depth by passing u >> u->parent >> u->parent.rson ...
	lcnt: #L rotate, will increase #L depth for left subtree
	rcnt: #R rotate, will increase #R depth for right subtree
*/
void dfs(Node *u, int lh, int rh, int lcnt, int rcnt) {
	if (u == NULL)	return;
	int lsonH = getHeight(u->lson);
	int rsonH = getHeight(u->rson);
	dp[u->label] = max(max(lh, rh), max(lsonH + lcnt, rsonH + rcnt)) + 1;
	dfs(u->lson, lh, max(rh, rsonH + rcnt + 1), lcnt, rcnt+1);
	dfs(u->rson, max(lh, lsonH + lcnt + 1), rh, lcnt+1, rcnt);
}
int main() {
	int n, lson, rson;
	while (scanf("%d", &n) == 1 && n) {
		
		memset(used2, 0, sizeof(used2));
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &lson, &rson);
			nodes[i].label = i;
			nodes[i].lson = nodes[i].rson = NULL;
			if (lson)
				nodes[i].lson = &nodes[lson];
			if (rson)
				nodes[i].rson = &nodes[rson];
			used2[lson] = used2[rson] = 1;
		}
		
				
		memset(used, 0, sizeof(used));
		for (int i = 1; i <= n; i++)
			getHeight(&nodes[i]);
			
		for (int i = 1; i <= n; i++) {
			if (used2[i] == 0) {
				Node *root = &nodes[i];
				dfs(root, 0, 0, 0, 0);
			}
		}
		for (int i = 1; i <= n; i++)
			printf("%d\n", dp[i]);
	}
	return 0;
}
/*
4
2 3
4 0
0 0
0 0

4
2 0
3 0
4 0
0 0

0
*/
