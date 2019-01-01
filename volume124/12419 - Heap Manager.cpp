#include <bits/stdc++.h> 
using namespace std;

struct DynamicST {
	const static int MAXN = 5000000;
	struct Node {
		Node *lson, *rson;
		int lazy;
		int mxzo, lxzo, rxzo;
		Node() {}
	} nodes[MAXN];
	int node_size;
	int n;
	Node *EMPTY, *root;
	void init(int n) {
		node_size = 0;
		EMPTY = newNode();
		this->n = n;
		root = EMPTY;
		_pushdown(root, 0, n-1, 0);
	}
	int malloc(int len, int &pos) {
		if (root->mxzo < len)
			return 0;
		pos = _find(root, 0, n-1, len);
		_update(root, 0, n-1, pos, pos+len-1, 1);
		return 1;
	}
	void free(int pos, int len) {
		_update(root, 0, n-1, pos, pos+len-1, 0);
	}
	void _pushdown(Node* &p, int l, int r, int val) {
		if (p == EMPTY)	p = newNode();
		p->mxzo = val == 0 ?  r-l+1 : 0;
		p->lxzo = p->rxzo = p->mxzo;
		p->lazy = val;
	}
	void pushdown(Node *u, int l, int r) {
		if (u->lazy >= 0) {
			int m = (l+r)/2;
			_pushdown(u->lson, l, m, u->lazy);
			_pushdown(u->rson, m+1, r, u->lazy);
			u->lazy = -1;
		}
	}
	void pushup(Node *u, int l, int r) {
		int m = (l+r)/2;
		u->lxzo = (u->lson->lxzo == m-l+1) ? u->lson->lxzo + u->rson->lxzo : u->lson->lxzo;
		u->rxzo = (u->rson->rxzo == r-m) ? u->lson->rxzo + u->rson->rxzo : u->rson->rxzo;
		u->mxzo = max(max(u->lxzo, u->rxzo), u->lson->rxzo + u->rson->lxzo);
		u->mxzo = max(u->mxzo, max(u->lson->mxzo, u->rson->mxzo));
	}
	Node* newNode() {
		Node *p = &nodes[++node_size];
		p->lson = p->rson = EMPTY;
		p->lazy = -1;
		return p;
	}
	void _update(Node *u, int l, int r, int ql, int qr, int val) {
		if (ql <= l && r <= qr) {
			_pushdown(u, l, r, val);
			return;
		}
		pushdown(u, l, r);
		int m = (l+r)/2;
		if (ql <= m)
			_update(u->lson, l, m, ql, qr, val);
		if (qr > m)
			_update(u->rson, m+1, r, ql, qr, val);
		pushup(u, l, r);
	}
	int _find(Node *u, int l, int r, int len) {
		if (u->lxzo >= len)	return l;
		pushdown(u, l, r);
		int m = (l+r)/2;
		if (u->lson->mxzo >= len)
			return _find(u->lson, l, m, len);
		if (u->lson->rxzo + u->rson->lxzo >= len)
			return m - u->lson->rxzo + 1;
		return _find(u->rson, m+1, r, len);
	}
} dst;

struct Event {
	int64_t t;
	int m, p;
	Event(int64_t t, int m, int p):
		t(t), m(m), p(p) {}
	bool operator<(const Event &e) const {
		return t > e.t;
	}
};

priority_queue<Event> free_evts;
queue<Event> Q;
int debug;
int64_t process_queue(int64_t t) {
	int64_t last;
	while (!free_evts.empty() && free_evts.top().t <= t) {
		int64_t free_time = free_evts.top().t;
		last = free_time;
		while (!free_evts.empty() && free_evts.top().t == free_time) {
			Event evt = free_evts.top(); free_evts.pop();
			dst.free(evt.p, evt.m);
		}
		while (!Q.empty()) {
			Event evt = Q.front();
			int pos;
			if (dst.malloc(evt.m, pos)) {
				Q.pop();
				free_evts.push(Event(free_time+evt.p, evt.m, pos));
				if (debug)
					printf("%lld %d %d\n", free_time, evt.t, pos);
			} else {
				break;
			}
		}
	}
	return last;
}
int main() {
	int n;
	int64_t t;
	int m, p;
	while (scanf("%d %d", &n, &debug) == 2) {
		dst.init(n);
		Q = queue<Event>();
		free_evts = priority_queue<Event>();
		int eid = 0, inq = 0;
		while (scanf("%lld %d %d", &t, &m, &p) == 3) {
			if (t == 0 && m == 0 && p == 0)
				break;
			eid++;
			process_queue(t);
			int pos;
			if (dst.malloc(m, pos)) {
				free_evts.push(Event(t+p, m, pos));
				if (debug)
					printf("%lld %d %d\n", t, eid, pos);
			} else {
				Q.push(Event(eid, m, p));
				inq++;
			}
		}
		int64_t finish = process_queue(1LL<<60);
		printf("%lld\n", finish);
		printf("%d\n\n", inq);
	}
	return 0;
}
/*
10 1
1 3 10
2 4 3
3 4 4
4 1 4
5 3 4
0 0 0

4 1
0 3 5
1 1 4
2 2 2
3 1 1
4 2 1
5 1 3
0 0 0

4 1
0 3 5
1 1 1
2 2 2
3 1 1
4 2 1
5 1 3
0 0 0
*/
