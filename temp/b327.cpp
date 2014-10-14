#include <stdio.h> 
#include <vector>
#include <set>
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 32767
struct Tree {
	vector<int> g[MAXN];
	int root;	
	void init(int n) {
		for (int i = 0; i < n; i++)
			g[i].clear();
		root = 0;
	}
	void addEdge(int x, int y) {
		g[x].push_back(y);
		g[y].push_back(x);
	}
} tree;
int bPos[MAXN], ePos[MAXN], inOrder[MAXN<<1], inIdx = 0;
void prepare(int u, int p) {
	bPos[u] = ePos[u] = ++inIdx, inOrder[inIdx] = u;
	for (int i = 0; i < tree.g[u].size(); i++) {
		int v = tree.g[u][i];
		if (v == p)	continue;
		prepare(v, u);
	}
	ePos[u] = ++inIdx, inOrder[inIdx] = u;
}

int bitTree[MAXN<<1];
void modify(int x, int N, int val) {
    while (x <= N) {
        bitTree[x] += val;
        x += x&(-x);
    }
}
int query(int x) {
    int ret = 0;
    while (x) {
        ret += bitTree[x];
        x -= x&(-x);
    }
    return ret;
}
int main() {
	int n, q, x, y;
	char cmd[10];
	while (scanf("%d", &n) == 1) {
		tree.init(n);
		
		int on[MAXN] = {};
		for (int i = 1; i < n; i++) {
			scanf("%d %d", &x, &y);
			tree.addEdge(x, y);
		}
		
		inIdx = 0;
		prepare(tree.root = 0, -1);
		memset(bitTree, 0, sizeof(bitTree));
		scanf("%d", &q);
		for (int i = 0; i < q; i++) {
			scanf("%d %d", &x, &y);
			modify(bPos[x], inIdx, y);
            modify(ePos[x] + 1, inIdx, -y);
			printf("%d\n", query(bPos[x]));
		}
		puts("");
	}
	return 0;
}
