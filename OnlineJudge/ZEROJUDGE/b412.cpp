#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

const int MAXN = 3000000;
class SegementTree {
public:
	struct Node {
		Node *lson, *rson;
	    pair<int, int> val;
	} nodes[MAXN];
	int nodesize, L, R;
	Node* init(int l, int r) {
		nodesize = 0;
		L = l, R = r;
		Node* root = build(l, r);
		return root;
	}
	Node* newNode() {
		if (nodesize >= MAXN)
			exit(0);
		return &nodes[nodesize++];
	}
	Node* cloneNode(Node *p) {
		if (nodesize >= MAXN)
			exit(0);
		Node* u = &nodes[nodesize++];
		*u = *p;
		return u;
	}
	Node* build(int l, int r) {
	    if (l > r)  return NULL;
	    Node *u = newNode();
	    u->lson = u->rson = NULL;
	    if (l == r) {
			u->val = make_pair(l, 1);
		} else {
			int m = (l + r)/2;
	    	u->lson = build(l, m);
	    	u->rson = build(m+1, r);
		}
	    return u;
	}
	Node* change(Node *p, int x, pair<int, int> val, int l, int r) {
		Node *u = cloneNode(p);
	    if (l == r) {
	    	u->val = val;
	    } else {
	    	int mid = (l + r)/2;
	    	if (x <= mid)
	        	u->lson = change(p->lson, x, val, l, mid);
	    	else
	     		u->rson = change(p->rson, x, val, mid+1, r);
	    }
	    return u;
	}
	Node* change(Node *p, int x, pair<int, int> val) {
		return change(p, x, val, L, R);
	}
	pair<int, int> find(Node *ver, int x, int l, int r) {
	    if (l == r)
	    	return ver->val;
	    int mid = (l + r)/2;
	    if (x <= mid)
	        return find(ver->lson, x, l, mid);
	    else
	        return find(ver->rson, x, mid+1, r);
	}
	pair<int, int> find(Node *ver, int x) {
	    return find(ver, x, L, R);
	}
	// disjoint set
	pair<int, int> findp(Node *ver, int x) {
		pair<int, int> p = find(ver, x);
		return x == p.first ? p : findp(ver, p.first);
	}
	Node* joint(Node *ver, int x, int y) {
		pair<int, int> a = findp(ver, x);
		pair<int, int> b = findp(ver, y);
		if (a.first == b.first)
			return ver;
		Node *u = ver;
		if (a.second > b.second) {
			u = change(u, b.first, make_pair(a.first, b.second));
			u = change(u, a.first, make_pair(a.first, a.second + b.second));
		} else {
			u = change(u, a.first, make_pair(b.first, a.second));
			u = change(u, b.first, make_pair(b.first, a.second + b.second));
		}
		return u;
	}
} segTree;
const int MAXQ = 262144;
SegementTree::Node *ver[MAXQ];

int main() {
	int n, m;
	int cmd, x, y, v;
	while (scanf("%d %d", &n, &m) == 2) {
		ver[0] = segTree.init(1, n);
		int encrypt = 0;
		for (int i = 1; i <= m; i++) {
			scanf("%d", &cmd);
			cmd ^= encrypt;
			if (cmd == 0) { 		// back
				scanf("%d", &v);
				v ^= encrypt;
				ver[i] = ver[v];
			} else if (cmd == 1) {	// joint
				scanf("%d %d", &x, &y);
				x ^= encrypt, y ^= encrypt; 
				ver[i] = segTree.joint(ver[i-1], x, y);
			} else if (cmd == 2) {	// find
				scanf("%d %d", &x, &y);
				x ^= encrypt, y ^= encrypt;
				pair<int, int> a = segTree.findp(ver[i-1], x);
				pair<int, int> b = segTree.findp(ver[i-1], y);
				int t = a.first == b.first;
				printf("%d\n", t);
				ver[i] = ver[i-1];
				encrypt = t;
			} else {
				puts("WTF");
				return 0;
			}
		}
	}
	return 0;
}
