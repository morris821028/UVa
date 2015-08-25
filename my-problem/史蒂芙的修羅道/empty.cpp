#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <vector>
using namespace std;
const int MAXN = 1<<22;
const int MAXQ = 1<<22;
struct Node {
	int idx, val;
	Node *ch[2], *fa;
	Node() {
		idx = val = 0;
		ch[0] = ch[1] = fa = NULL;
	}
} nodes[MAXN];
int A[MAXN], N;
vector< pair<int, int> > Q[MAXN];
int visited[MAXN], parent[MAXN], ret[MAXQ];
void init(int n, int q) {
	N = n;
	for (int i = 0; i <= n; i++) {
		Q[i].clear();
		parent[i] = i, visited[i] = 0;
	}
}
void insert(Node *u, Node *p) {
	while (p->val < u->val)	p = p->fa;
	u->ch[0] = p->ch[1];
	if (p->ch[1])	p->ch[1]->fa = u;
	p->ch[1] = u;
	u->fa = p;
}
void build() {
	nodes[0] = Node(), nodes[0].val = INT_MAX;
	for (int i = 1; i <= N; i++) {
		nodes[i] = Node();
		nodes[i].val = A[i], nodes[i].idx = i;
		insert(&nodes[i], &nodes[i-1]);
	}
}
int findp(int x) {
	return parent[x] == x ? x : parent[x]=findp(parent[x]);
}
void tree_reverse(Node *from, Node *to) {
	if (from == to)	return ;
	Node *x = from, *y = from->ch[1], *z;
	while (true) {
		z = y->ch[1];
		y->ch[1] = x;
		x = y, y = z;
		if (x == to)
			return ;
	}
}
void print_reverse(Node *from, Node *to) {
	tree_reverse(from, to);
	Node *p = to;
	while (true) {
		int u = p->idx;
		visited[u] = 1;
		for (int i = 0; i < Q[u].size(); i++) {
			if (visited[Q[u][i].second])
				ret[Q[u][i].first] = A[findp(Q[u][i].second)];
		}
		if (p->fa != NULL)	parent[findp(u)] = p->fa->idx;
		if (p == from)	break;
		p = p->ch[1];
	}		
	tree_reverse(to, from);
}
void tarjan(Node *root) {	
	Node *cur, *prev, tmp;
	tmp.ch[0] = root;
	cur = &tmp, prev = NULL;
	while (cur != NULL) {
		if (cur->ch[0] == NULL) {
			cur = cur->ch[1];
		} else {
			prev = cur->ch[0];
			while (prev->ch[1] != NULL && prev->ch[1] != cur)
				prev = prev->ch[1];
			if (prev->ch[1] == NULL) {
				prev->ch[1] = cur, cur = cur->ch[0];
			} else {
				print_reverse(cur->ch[0], prev);
				prev->ch[1] = NULL, cur = cur->ch[1];
			}
		}
	}
}
void add(int x, int y, int qid) {
	Q[x].push_back({qid, y});
	Q[y].push_back({qid, x});
}
void offline() {
	build();
	tarjan(nodes[0].ch[1]);
}
int main() {
	int N, Q, x, y;
	while (scanf("%d", &N) == 1) {
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		scanf("%d", &Q);
		for (int i = 0; i < Q; i++) {
			scanf("%d %d", &x, &y);
		}
		for (int i = 0; i < Q; i++)
			printf("%d\n", x);
	}
	return 0;
}
