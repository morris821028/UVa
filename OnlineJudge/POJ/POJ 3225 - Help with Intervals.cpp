#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1<<20, INF = 0x3f3f3f3f;
class SegmentTree {
public:
	struct Node {
		int val;
		pair<int, int> cdel, idel;	// cover, inverse
		void init(int a = 0) {
			val = a;
			cdel = idel = {0, 0};
		}
		
	} nodes[MAXN];
	void pushDown(int k, int l, int r) {
		if (nodes[k].cdel.first) {
			nodes[k<<1].cdel = nodes[k].cdel, nodes[k<<1].idel = {0, 0};
			nodes[k<<1|1].cdel = nodes[k].cdel, nodes[k<<1|1].idel = {0, 0};
			nodes[k].cdel = {0, 0};
		}
		if (nodes[k].idel.first) {
			if (nodes[k<<1].cdel.first)
				nodes[k<<1].cdel.second ^= 1;
			else
				nodes[k<<1].idel.first ^= 1;
			if (nodes[k<<1|1].cdel.first)
				nodes[k<<1|1].cdel.second ^= 1;
			else
				nodes[k<<1|1].idel.first ^= 1;
			nodes[k].idel = {0, 0};
		}
	}
	void pushUp(int k, int l, int r) {
		
	}
	void build(int k, int l, int r) { 
		nodes[k].init(0);
		if (l == r)	return ;
		int mid = (l + r)/2;
		build(k<<1, l, mid);
		build(k<<1|1, mid+1, r);
		pushUp(k, l, r);
	} 
	void assign(int k, int l, int r, int x, int y, int val) {
		if (x > y)	return ;
		if (x <= l && r <= y) {
			nodes[k].cdel = {1, val};
			nodes[k].idel = {0, 0};
			return;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)	assign(k<<1, l, mid, x, y, val);
		if (y > mid)	assign(k<<1|1, mid+1, r, x, y, val);
		pushUp(k, l, r);
	}
	void inverse(int k, int l, int r, int x, int y) {
		if (x > y)	return ;
		if (x <= l && r <= y) {
			if (nodes[k].cdel.first)
				nodes[k].cdel.second ^= 1;
			else
				nodes[k].idel.first ^= 1;
			return;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)	inverse(k<<1, l, mid, x, y);
		if (y > mid)	inverse(k<<1|1, mid+1, r, x, y);
		pushUp(k, l, r);
	}
	//
	vector<int> opos;
	void clear_all(int k, int l, int r) {
		if (l == r) {
			if (nodes[k].cdel.second)
				opos.push_back(l);
			return ;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		clear_all(k<<1, l, mid);
		clear_all(k<<1|1, mid+1, r);
		pushUp(k, l, r);
	}
} tree;

int main() {
	int N = 65536<<1;
	tree.build(1, 0, N);
	
	int l, r;
	char lc, rc, cmd[8];
	while (scanf("%s %c%d,%d%c", cmd, &lc, &l, &r, &rc) == 5) {
		l <<= 1, r <<= 1;
		if (lc == '(')	l++;
		if (rc == ')')	r--;
		if (cmd[0] == 'U') {
			tree.assign(1, 0, N, l, r, 1);
		} else if (cmd[0] == 'I') {
			tree.assign(1, 0, N, 0, l-1, 0);
			tree.assign(1, 0, N, r+1, N, 0);
		} else if (cmd[0] == 'D') {
			tree.assign(1, 0, N, l, r, 0);
		} else if (cmd[0] == 'C') {
			tree.assign(1, 0, N, 0, l-1, 0);
			tree.assign(1, 0, N, r+1, N, 0);
			tree.inverse(1, 0, N, l, r);
		} else {
			tree.inverse(1, 0, N, l, r);
		}
	}
	
	tree.opos.clear();
	tree.clear_all(1, 0, N);
	
	if (tree.opos.size() == 0) {
		puts("empty set");
	}
	for (int i = 0; i < tree.opos.size(); )  {
		int l = tree.opos[i], r = tree.opos[i];
		while (i < tree.opos.size() && tree.opos[i] == r)
			r++, i++;
		r--;
		int a, b;
		if (l%2)	printf("(%d", l/2);
		else		printf("[%d", l/2);
		if (r%2)	printf(",%d)", r/2+1);
		else		printf(",%d]", r/2);
		printf(" ");
	}
	return 0;
}
/*
U [1,5]
D [3,3]
S [2,4]
C (1,5)
I (2,3]
*/
