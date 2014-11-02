#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAXN (1<<23)
#define MAXQ 65536
struct node;
node *null;
struct node {
	node *lson, *rson;
	int key, size;
	char label; // user def label
	
	node(char c = 0, int s = 1):label(c), size(s) {
		lson = rson = null;
		key = rand();
	}
	void update() {
		size = 1;
		size += lson->size + rson->size;	
	}
} nodes[MAXN], *root[MAXQ];
struct treap {
	int bufIdx = 0;
	int prob_c; // this problem need.
	node* getNode(node* u) {
		node *ret;
		if (u == null) {
			return u;
		} else {
			ret = &nodes[bufIdx++];
			*ret = *u;
			return ret;
		}
	}
	node* merge(node* a, node* b) {
		if (a == null)	return getNode(b);
		if (b == null)	return getNode(a);
		node *ret;
		if (a->key < b->key) {
			ret = getNode(a);
			ret->rson = merge(a->rson, b);
		} else {
			ret = getNode(b);
			ret->lson = merge(a, b->lson);
		}
		ret->update();
		return ret;
	}
	void split(node* a, node* &l, node* &r, int n) {
		if (n == 0) {
			l = null, r = getNode(a);
		} else if (a->size <= n) {
			l = getNode(a), r = null;
		} else if (a->lson->size >= n) {
			r = getNode(a);
			split(a->lson, l, r->lson, n);
			r->update();
		} else {
			l = getNode(a);
			split(a->rson, l->rson, r, n - (a->lson->size) - 1);
			l->update();
		}
	}
	void build(node* &a, int l, int r, char s[]) {
		if (l > r)	return ;
		int m = (l + r) /2;
		node u = node(s[m]), *p = &u, *q;
		a = getNode(p), p = null, q = null;
		build(p, l, m-1, s);
		build(q, m+1, r, s);
		p = merge(p, a);
		a = merge(p, q);
		a->update();
	}
	void insert(node* &a, node *ver, int pos, char s[]) {
		node *p, *q, *r;
		int n = strlen(s);
		split(ver, p, q, pos);
		build(r, 0, n - 1, s);
		p = merge(p, r);
		a = merge(p, q);
	}
	void remove(node* &a, node *ver, int pos, int n) {
		node *p, *q, *r;
		split(ver, p, q, pos - 1);
		split(q, q, r, n);
		a = merge(p, r);
	}
	void print(node *ver) {
		if (ver == null)	return;
		print(ver->lson);
		if (ver->label == 'c')	prob_c++; // this problem need
		putchar(ver->label);
		print(ver->rson);
	}
	void printdebug(node *ver) {
		if (ver == null)	return;
		print(ver->lson);
		putchar(ver->label);
		print(ver->rson);
	}
	void traversal(node *ver, int pos, int n) {
		node *p, *q, *r;
		split(ver, p, q, pos - 1);
		split(q, q, r, n);
		print(q);
	}
	void init() {
		bufIdx = 0; 
		prob_c = 0;
		null = &nodes[bufIdx++];
		null->size = 0;
	}
} tree;
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		tree.init();
		int cmd, v, p, c, verIdx;
		char s[128];
		root[verIdx = 0] = null;
		for (int i = 0; i <= n; i++)
			root[i] = null;
		for (int i = 0; i < n; i++) {
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d %s", &p, s);
				p -= tree.prob_c;
				tree.insert(root[verIdx + 1], root[verIdx], p, s);
				verIdx++;
			} else if (cmd == 2) {
				scanf("%d %d", &p, &c);
				p -= tree.prob_c, c -= tree.prob_c;
				tree.remove(root[verIdx + 1], root[verIdx], p, c);
				verIdx++;
			} else {
				scanf("%d %d %d", &v, &p, &c);
				v -= tree.prob_c, p -= tree.prob_c, c -= tree.prob_c;
				tree.traversal(root[v], p, c);
				puts("");
			}
		}
	}
	return 0;
}
/*
6
1 0 abcdefgh
2 4 3
3 1 2 5
3 3 3 4
1 4 xy
3 5 4 6
*/
