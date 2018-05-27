#include <bits/stdc++.h> 
using namespace std;

struct Rect {
	int lx, ly, rx, ry;
};
struct Event {
	int x, l, r, val;
	Event(int x=0, int l=0, int r=0, int val=0):
		x(x), l(l), r(r), val(val) {}
	bool operator<(const Event &other) const {
		return x < other.x;
	}
};
struct Node {
	int sum, cov;
};
static const int MAXN = 50005;
static Node tree[281072];
static int Y[MAXN*2];
void init_tree(int k, int l, int r) {
	tree[k].sum = tree[k].cov = 0;
	if (l >= r)
		return ;
	int m = (l+r)/2;
	init_tree(k<<1, l, m);
	init_tree(k<<1|1, m+1, r);
}
int pushup(int k, int l, int r) {
	if (tree[k].sum > 0)
		tree[k].cov = Y[r+1] - Y[l];
	else if (l == r)
		tree[k].cov = 0;
	else
		tree[k].cov = tree[k<<1].cov + tree[k<<1|1].cov;
}
void draw_tree(int k, int l, int r, int x, int y, int val) {
	if (x <= l && r <= y) {
		tree[k].sum += val;
		pushup(k, l, r);
		return ;
	}
	int m = (l+r)/2;
	if (x <= m)
		draw_tree(k<<1, l, m, x, y, val);
	if (y > m)
		draw_tree(k<<1|1, m+1, r, x, y, val);
	pushup(k, l, r);
} 
int64_t union_rectangle(vector<Event> &X, int w, int h) {
	int64_t ret = 0;
	int ysize = 0, n;
	
	sort(X.begin(), X.end());
	n = X.size();
	for (int i = 0; i < n; i++) {
		Y[ysize++] = X[i].l;
		Y[ysize++] = X[i].r;
	}

	sort(Y, Y+ysize);
	ysize = unique(Y, Y+ysize) - Y;
	init_tree(1, 0, ysize-2);

	for (int i = 0; i < n; i++) {
		int l = lower_bound(Y, Y+ysize, X[i].l)-Y;
		int r = lower_bound(Y, Y+ysize, X[i].r)-Y;
		draw_tree(1, 0, ysize-2, l, r-1, X[i].val);
		if (i < n && X[i].x != X[i+1].x)
			ret += (int64_t) tree[1].cov * (X[i+1].x - X[i].x);
	}
	return (int64_t) h*w - ret;
}

int main() {
	int w, h, n, m;
	static Rect rect[MAXN];
	while (scanf("%d %d %d %d", &w, &h, &n, &m) == 4) {
		for (int i = 0; i < n; i++)
			scanf("%d %d %d %d", &rect[i].lx, &rect[i].ly, &rect[i].rx, &rect[i].ry);

		vector<Event> X, Y;
		X.reserve(2*n+2), Y.reserve(2*n+2);
		for (int i = 0; i < n; i++) {
			X.push_back(Event(rect[i].lx-1, max(0, rect[i].ly-m), rect[i].ry, 1));
			X.push_back(Event(rect[i].rx, max(0, rect[i].ly-m), rect[i].ry, -1));
			
			Y.push_back(Event(rect[i].ly-1, max(0, rect[i].lx-m), rect[i].rx, 1));
			Y.push_back(Event(rect[i].ry, max(0, rect[i].lx-m), rect[i].rx, -1));
		}
		X.push_back(Event(0, max(0, h-m+1), h, 1));
		X.push_back(Event(w, max(0, h-m+1), h, -1));
		
		Y.push_back(Event(0, max(0, w-m+1), w, 1));
		Y.push_back(Event(h, max(0, w-m+1), w, -1));
		
		int64_t ret = 0;
		ret += union_rectangle(X, w, h);
		if (m != 1)
			ret += union_rectangle(Y, h, w);
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3 3 1 2
2 2 2 2

3 3 1 3
2 2 2 2

2 3 2 2
1 1 1 1
2 3 2 3

3 3 0 2
*/
