#include <stdio.h> 
#include <algorithm>
using namespace std;
const int MAXN = 524288;
class SegmentTree {
public:
	struct Node {
		long long sum, sqr, mx, mn;
		pair<int, long long> label[2];
		void init() {
			sum = sqr = 0;
			mx = -1LL<<60, mn = 1LL<<60;
			label[0] = label[1] = make_pair(0, 0);
		}
	} nodes[MAXN];
	long long A[MAXN];
	void pushDown(int k, int l, int r) {
		int mid = (l + r)/2;
		if (nodes[k].label[0].first) {
			assignUpdate(k<<1, l, mid, nodes[k].label[0].second);
			assignUpdate(k<<1|1, mid+1, r, nodes[k].label[0].second);
			nodes[k].label[0] = make_pair(0, 0); // cancel
		}
		if (nodes[k].label[1].first) {
			addUpdate(k<<1, l, mid, nodes[k].label[1].second);
			addUpdate(k<<1|1, mid+1, r, nodes[k].label[1].second);
			nodes[k].label[1] = make_pair(0, 0); // cancel
		}
	}
	void pushUp(int k) {
		nodes[k].sum = nodes[k<<1].sum + nodes[k<<1|1].sum;
		nodes[k].sqr = nodes[k<<1].sqr + nodes[k<<1|1].sqr;
		nodes[k].mx = max(nodes[k<<1].mx, nodes[k<<1|1].mx);
		nodes[k].mn = min(nodes[k<<1].mn, nodes[k<<1|1].mn);
	}
	void build(int k, int l, int r) { 
		nodes[k].init();
		if (l == r) {
			nodes[k].sum = A[l];
			nodes[k].sqr = A[l] * A[l];
			nodes[k].mx = nodes[k].mn = A[l];
			return ;
		}
		int mid = (l + r)/2;
		build(k<<1, l, mid);
		build(k<<1|1, mid+1, r);
		pushUp(k);
	} 
	// operator, assign > add
	void assignUpdate(int k, int l, int r, long long val) {
		nodes[k].label[0] = make_pair(1, val);
		nodes[k].label[1] = make_pair(0, 0); // cancel lower priority
		nodes[k].sum = (long long) (r - l + 1) * val;
		nodes[k].sqr = (long long) (r - l + 1) * val * val;
		nodes[k].mn = nodes[k].mx = val;
	}
	void addUpdate(int k, int l, int r, long long val) {
		nodes[k].label[1].first = 1;
		nodes[k].label[1].second += val;
		nodes[k].sqr += 2LL * val * nodes[k].sum + (long long) (r - l + 1) * val * val;
		nodes[k].sum += (long long) (r - l + 1) * val;
		nodes[k].mn += val;
		nodes[k].mx += val;
	}
	void assign(int k, int l, int r, int x, int y, int val) {
		if (x <= l && r <= y) {
			assignUpdate(k, l, r, val);
			return;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			assign(k<<1, l, mid, x, y, val);
		if (y > mid)
			assign(k<<1|1, mid+1, r, x, y, val);
		pushUp(k);
	}
	void add(int k, int l, int r, int x, int y, int val) {
		if (x <= l && r <= y) {
			addUpdate(k, l, r, val);
			return;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			add(k<<1, l, mid, x, y, val);
		if (y > mid)
			add(k<<1|1, mid+1, r, x, y, val);
		pushUp(k);
	}
	// query 
	long long r_sum, r_sqr, r_mx, r_mn;
	void qinit() {
		r_sum = r_sqr = 0;
		r_mx = -1LL<<60, r_mn = 1LL<<60;
	}
	void query(int k, int l, int r, int x, int y) {
		if (x <= l && r <= y) {
			r_sum += nodes[k].sum;
			r_sqr += nodes[k].sqr;
			r_mx = max(r_mx, nodes[k].mx);
			r_mn = min(r_mn, nodes[k].mn);
			return ;
		}
		pushDown(k, l, r);
		int mid = (l + r)/2;
		if (x <= mid)
			query(k<<1, l, mid, x, y);
		if (y > mid)
			query(k<<1|1, mid+1, r, x, y);
	}
} tree;
long long llgcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
int main() {
	int testcase, cases = 0;
	int n, q;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &q);
		for (int i = 1; i <= n; i++)
			scanf("%lld", &tree.A[i]);
			
		tree.build(1, 1, n);
		
		printf("Case %d:\n", ++cases);
		for (int i = 0; i < q; i++) {
			int cmd, l, r, val;
			scanf("%d", &cmd);
			if (cmd == 0) { // assign [l, r] = val
				scanf("%d %d %d", &l, &r, &val);
				tree.assign(1, 1, n, l, r, val);
			} else if (cmd == 1) { // add [l, r] = val
				scanf("%d %d %d", &l, &r, &val);
				tree.add(1, 1, n, l, r, val);
			} else if (cmd == 2) {
				scanf("%d %d", &l, &r);
				
				tree.qinit();
				tree.query(1, 1, n, l, r);
				
				long long m = (r - l + 1), g;
				long long a = tree.r_sqr * m - tree.r_sum * tree.r_sum;
				long long b = m * m;
				g = llgcd(a, b);
				a /= g, b /= g;
				printf("%lld/%lld ", a, b);
				printf("%lld\n", tree.r_mx - tree.r_mn);
			}
		}
	}
	return 0;
}

/*
999

9 6
-1 3 2 4 -2 8 0 5 -7
2 3 6
0 5 5 2
2 3 6
1 4 7 1
2 3 7
2 1 1

9 6
-1 3 2 4 -2 8 0 5 -7
2 3 6
0 5 5 2
2 3 6
1 4 7 1
2 3 7
2 1 1
*/
