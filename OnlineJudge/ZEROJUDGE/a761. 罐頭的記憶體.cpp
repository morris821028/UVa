#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1<<21, INF = 0x3f3f3f3f;
class SegmentTree {
public:
	struct Node {
		int val, del;
		void init(int a = 0, int b = 0) {
			val = a, del = b;
		}
	} nodes[MAXN];
	void pushDown(int k, int l, int r) {
		if (nodes[k].del != INF) {
			nodes[k<<1].val = min(nodes[k<<1].val, nodes[k].del);
			nodes[k<<1].del = min(nodes[k<<1].del, nodes[k].del);
			nodes[k<<1|1].val = min(nodes[k<<1|1].val, nodes[k].del);
			nodes[k<<1|1].del = min(nodes[k<<1|1].del, nodes[k].del);
			nodes[k].del = INF;
		}
	}
	void pushUp(int k, int l, int r) {
		nodes[k].val = min(nodes[k<<1].val, nodes[k<<1|1].val);
	}
	void build(int k, int l, int r) { 
		nodes[k].init(INF, INF);
		if (l == r)	return ;
		int mid = (l + r)/2;
		build(k<<1, l, mid);
		build(k<<1|1, mid+1, r);
		pushUp(k, l, r);
	} 
	void assignUpdate(int k, int l, int r, int val) {
		nodes[k].del = min(nodes[k].del, val);
		nodes[k].val = min(nodes[k].val, val);
	}
	void assign(int k, int l, int r, int x, int y, int val) {
		if (x <= l && r <= y) {
			assignUpdate(k, l, r, val);
			return;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)	assign(k<<1, l, mid, x, y, val);
		if (y > mid)	assign(k<<1|1, mid+1, r, x, y, val);
		pushUp(k, l, r);
	}
	int query(int k, int l, int r, int x) {
		if (x <= l && r <= x || nodes[k].val == INF)
			return nodes[k].val;
		pushDown(k, l, r);
		int mid = (l + r)/2, ret;
		if (x <= mid)	ret = query(k<<1, l, mid, x);
		else			ret = query(k<<1|1, mid+1, r, x);
		pushUp(k, l, r);
		return ret;
	}
	int query(int k, int l, int r, int x, int y) {
		if (x <= l && r <= y || nodes[k].val == INF)
			return nodes[k].val;
		pushDown(k, l, r);
		int mid = (l + r)/2, ret = INF;
		if (x <= mid)
			ret = min(ret, query(k<<1, l, mid, x, y));
		if (y > mid)
			ret = min(ret, query(k<<1|1, mid+1, r, x, y));
		pushUp(k, l, r);
		return ret;
	}
} tree;

const int MAXQ = 524288;
char cmd[MAXQ][8];
int args[MAXQ][3];
int main() {
	int N;
	while (scanf("%d", &N) == 1) {
		map<int, int> R;
		for (int i = 0; i < N; i++) {
			scanf("%s", &cmd[i]);
			int a, b, c;
			if (cmd[i][0] == 'l')
				scanf("%d", &a), R[a] = 0;
			else if (cmd[i][0] == 'm')
				scanf("%d %d %d", &a, &b, &c), R[b] = R[c] = 0;
			else
				scanf("%d", &a), R[a] = 0;
			args[i][0] = a, args[i][1] = b, args[i][2] = c;
		}
		
		int size = 0;
		for (auto &x : R)
			x.second = ++size;
		tree.build(1, 1, size);
		for (int i = 0; i < N; i++) {
			int a, b, c, t;
			a = args[i][0], b = args[i][1], c = args[i][2];
			if (cmd[i][0] == 'l') {
				t = tree.query(1, 1, size, R[a]);
				if (t == INF)
					printf("fail to load from %d\n", a);
				else
					printf("load from region %d\n", t);
			} else if (cmd[i][0] == 'm') {
				t = tree.query(1, 1, size, R[b], R[c]);
				if (t != INF)
					printf("fail to create region %d, overlap with region %d\n", a, t);
				else
					printf("region %d created\n", a), tree.assign(1, 1, size, R[b], R[c], a);
			} else {
				t = tree.query(1, 1, size, R[a]);
				if (t == INF)
					printf("fail to store to %d\n", a);
				else
					printf("store to region %d\n", t);
			}
		}
	}
	return 0;
}
/*
7
load 29
map 1 25 39
map 2 23 24
map 3 22 25
map 4 25 40
store 33   
store 22   
*/
