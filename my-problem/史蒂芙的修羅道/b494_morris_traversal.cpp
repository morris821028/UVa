#include <bits/stdc++.h>
using namespace std;
const int MAXN = 5000005, MAXQ = 5000005;
struct Node {
	int idx;
	Node *ch[2], *fa;
	Node() {
		idx = 0;
		ch[0] = ch[1] = fa = NULL;
	}
} nodes[MAXN];
struct QEdge {
	int u;
	QEdge *next;
};
QEdge qedge[MAXQ], *qadj[MAXN] = {};
unsigned int A[MAXN], eq, ret;
int parent[MAXN];
void init(int n) {
	eq = 0;
	for (int i = 0; i <= n; i++)
		parent[i] = i /*, qadj[i] = NULL */;
}
void insert(Node *u, Node *p) {
	while (A[p->idx] < A[u->idx])	p = p->fa;
	u->ch[0] = p->ch[1];
	if (p->ch[1])	p->ch[1]->fa = u;
	p->ch[1] = u;
	u->fa = p;
}
void build(int N) {
	nodes[0] = Node(), A[0] = UINT_MAX;
	for (int i = 1; i <= N; i++) {
		nodes[i] = Node(), nodes[i].idx = i;
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
		for (QEdge *e = qadj[u]; e; e = e->next) {
			if (findp(e->u) != e->u)
				ret ^= A[findp(e->u)];
			else
				ret ^= A[e->u];
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
	if (x < y)	swap(x, y);
	qedge[eq].u = y, qedge[eq].next = qadj[x], qadj[x] = &qedge[eq++];
}
unsigned int seed = 0;
unsigned int gen() {return seed = (seed*9301+49297);}
int N, M, S, x, y;
int main() {
	scanf("%d %d %d", &N, &M, &S);
	seed = S, init(N);
	for (int i = 1; i <= N; i++)
		x = gen(), A[i] = x;
	for (int i = 0; i < M; i++) {
		x = gen()%N+1, y = gen()%N+1;
		add(x, y, i);
	}
	ret = 0;
	build(N), tarjan(nodes[0].ch[1]);
	printf("%lu\n", ret);
	return 0;
}
