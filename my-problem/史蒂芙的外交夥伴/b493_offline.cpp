#include <bits/stdc++.h> 
using namespace std;

class SegementTree {
public:
	static const int MAXN = 1000000;
	struct Node {
		Node *lson, *rson;
		int sum;
	    Node() {
	    	lson = rson = NULL;
	    	sum = 0;
	    }
	} nodes[MAXN];
	int nodesize, L, R;
	Node* init(int l, int r) {
		nodesize = 0;
		L = l, R = r;
		Node* root = build(l, r);
		return root;
	}
	Node* newNode() {
		Node *u = &nodes[nodesize++];
		*u = Node();
		return u;
	}
	Node* cloneNode(Node *p) {
		Node* u = &nodes[nodesize++];
		*u = *p;
		return u;
	}
	Node* build(int l, int r) {
	    if (l > r)  return NULL;
	    Node *u = newNode();
	    if (l == r) {
		} else {
			int m = (l + r)/2;
	    	u->lson = build(l, m);
	    	u->rson = build(m+1, r);
		}
	    return u;
	}
	Node* change(Node *p, int x, int l, int r) {
		Node *u = cloneNode(p);
		u->sum++;
	    if (l == r) {
	    } else {
	    	int mid = (l + r)/2;
	    	if (x <= mid)
	        	u->lson = change(p->lson, x, l, mid);
	    	else
	     		u->rson = change(p->rson, x, mid+1, r);
	    }
	    return u;
	}
	Node* change(Node *p, int x) {
		return change(p, x, L, R);
	}
	
	int QD;
	void find(Node *v1, Node *v2, Node *v3, int x, int l, int r) {
		if (1 <= l && r <= x) {
	    	QD += v1->sum + v2->sum - v3->sum * 2;
	    	return ;
	    }
	    int mid = (l + r)/2;
	    if (x <= mid) {
	        find(v1->lson, v2->lson, v3->lson, x, l, mid);
	    } else {
			find(v1->lson, v2->lson, v3->lson, x, l, mid);
			find(v1->rson, v2->rson, v3->rson, x, mid+1, r);
		}
	}
	void find(Node *v1, Node *v2, Node *v3, int x) {
		QD = 0;
	    find(v1, v2, v3, x, L, R);
	}
} tree;
const int MAXN = 65536;
const int MAXLOGN = 17;
SegementTree::Node *root[MAXN];

struct Event {
	int x, y, k, cmd;
	void read() {
		scanf("%d %d %d", &cmd, &x, &y);
		if (cmd == 1)	scanf("%d", &k);
	}
};

int A[MAXN];
int fa[MAXLOGN][MAXN], visited[MAXN], dep[MAXN];
int parent[MAXN];
vector<int> g[MAXN];
void dfs(int u, int p) {
	visited[u] = 1;
	root[u] = tree.change(root[p], A[u]);
	for (auto v : g[u]) {
		if (v == p)	continue;
		fa[0][v] = u;
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
}
int findp(int x) {
    return x == parent[x] ? x : (parent[x]=findp(parent[x]));
}
int LCA(int x, int y) {
	if (dep[x] < dep[y])	swap(x, y);
	int d = dep[x] - dep[y];
	for (int i = MAXLOGN-1; i >= 0; i--) {
		if ((d>>i)&1) {
			d -= 1<<i;
			x = fa[i][x];
		}
	}
	if (x == y)	return x;
	for (int i = MAXLOGN-1; i >= 0; i--) {
		if (fa[i][x] != fa[i][y]) {
			x = fa[i][x], y = fa[i][y];
		}
	}
	return fa[0][x];
}

int main() {
	int N, Q;
	int L, R, K;
	while (scanf("%d %d", &N, &Q) == 2) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		vector<Event> e(Q);
		for (int i = 1; i <= N; i++)
			parent[i] = i, g[i].clear(), dep[i] = 0;
		for (int i = 0; i < Q; i++) {
			e[i].read();
			if (e[i].cmd == 0 && findp(e[i].x) != findp(e[i].y)) {
				g[e[i].y].push_back(e[i].x);
				g[e[i].x].push_back(e[i].y);
				parent[findp(e[i].x)] = findp(e[i].y);
			}
		}
		
		for (int i = 1; i <= N; i++)
			parent[i] = i, visited[i] = 0;
		
		root[0] = tree.init(1, N);
				
		memset(visited, 0, (N+1) * sizeof(visited[0]));
		for (int i = 1; i <= N; i++) {
			if (visited[i] == 0)
				dfs(i, 0);
		}
		
		for (int i = 1; i < MAXLOGN; i++) {
			for (int j = 1; j <= N; j++) {
				fa[i][j] = fa[i-1][fa[i-1][j]];
			}
		}
		
		for (int i = 0; i < Q; i++) {
			int x = e[i].x, y = e[i].y, k = e[i].k;
			if (e[i].cmd == 0) {
					x = findp(x), y = findp(y);
				if (x != y) {
					if (dep[x] < dep[y])
						parent[y] = x;
					else
						parent[x] = y;
				}
			} else {
				int rx, ry, lca;
				rx = findp(x), ry = findp(y);
				if (rx != ry) {
					puts("0");
					continue;
				}
				lca = LCA(x, y);
//				printf("fff %d %d, LCA(%d %d) = %d\n", rx, ry, x, y, lca);
				tree.find(root[x], root[y], root[lca], k);
				tree.QD += A[lca] <= k;
				printf("%d\n", tree.QD);
			}
		}
	}
	return 0;
}
/*
7 11
1 5 2 6 3 7 4
0 2 4
0 1 2
0 1 3
0 3 7
1 4 7 3
1 5 6 7
0 2 5
0 5 3
1 4 5 5
0 3 6
1 5 6 4
*/
