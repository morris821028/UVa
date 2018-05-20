#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 262144;

struct Pt3D {
	int x, y, z;
	Pt3D(int x=0, int y=0, int z=0):
		x(x), y(y), z(z) {}
};

struct Node {
	int mn, mx;
	int64_t sum;
};
Node tree[MAXN<<1];

void build(int k, int l, int r) {
	tree[k].mn = tree[k].mx = 0;
	tree[k].sum = 0;
	if (l == r)
		return ;
	int m = (l+r)/2;
	build(k<<1, l, m);
	build(k<<1|1, m+1, r);
}

void split(int k, int l, int r) {
	int m = (l+r)/2;
	tree[k<<1].mn = tree[k<<1].mx = tree[k].mn;
	tree[k<<1|1].mn = tree[k<<1|1].mx = tree[k].mn;
	tree[k<<1].sum = (int64_t) tree[k].mn*(m-l+1);
	tree[k<<1|1].sum = tree[k].sum - tree[k<<1].sum;
}

void update(int k, int l, int r, int x, int y, int v) {
	if (tree[k].mn >= v)
		return ;
	if (tree[k].mx < v) {
		if (tree[k].mx == tree[k].mn) {
			if (x <= l && r <= y) {
				tree[k].mn = tree[k].mx = v;
				tree[k].sum = (int64_t) (r-l+1)*v;
				return ;
			} else {
				split(k, l, r);
			}
		}
	}
	int m = (l+r)/2;
	if (x <= m)
		update(k<<1, l, m, x, y, v);
	if (y > m)
		update(k<<1|1, m+1, r, x, y, v);
	tree[k].mx = max(tree[k<<1].mx, tree[k<<1|1].mx);
	tree[k].mn = min(tree[k<<1].mn, tree[k<<1|1].mn);
	tree[k].sum = tree[k<<1].sum + tree[k<<1|1].sum;
}

int main() {
	int n, m;
	static Pt3D pts[MAXN];
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			pts[i] = Pt3D(x, y, z);
		}

		sort(pts, pts+n, [](const Pt3D &a, const Pt3D &b) {
			if (a.x != b.x)
				return a.x > b.x;
			return a.z < b.z;
		});
	
		int64_t ret = (int64_t) m*m*m;
		// Total - OR Volume
		build(1, 1, m);

		for (int i = 0; i < n; ) {
			int r = pts[i].x, l;
			while (i < n && pts[i].x == r) {
				update(1, 1, m, 1, pts[i].y, pts[i].z);
				i++;
			}
			if (i < n)
				l = pts[i].x;
			else
				l = 0;
			ret -= tree[1].sum*(r-l);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3 10
2 8 5
6 3 5
1 3 9

1 3
2 2 2

1 10000
2 2 2
*/
