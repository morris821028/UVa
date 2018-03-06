#include <bits/stdc++.h> 
using namespace std;

const int MAXV = 2005;
// Kuhn-Munkres Algorithm
struct KM {
	int _mem[MAXV*MAXV];
	int *w[MAXV];
	int lx[MAXV], ly[MAXV];
	int16_t mx[MAXV], my[MAXV];
	int16_t aug[MAXV], vis[MAXV];
	pair<int, int> slack[MAXV];
	int nx, ny;
	int match() {
		for (int i = 0; i < nx; i++)
			lx[i] = *max_element(w[i], w[i]+ny);
		fill(ly, ly+ny, 0);
		fill(mx, mx+nx, -1);
		fill(my, my+ny, -1);
		fill(slack, slack+ny, make_pair(0, 0));
		for (int root = 0; root < nx; root++) {
			fill(aug, aug+ny, -1);
			fill(vis, vis+nx, 0);
			vis[root] = 1;
			for (int y = 0; y < ny; y++)
				slack[y] = make_pair(lx[root]+ly[y]-w[root][y], root);
			int sy = -1;
			for (;;) {
				int delta = INT_MAX, sx = -1;
				for (int y = 0; y < ny; y++) {
					if (aug[y] == -1 && slack[y].first < delta) {
						delta = slack[y].first;
						sx = slack[y].second, sy = y;
					}
				}
//				assert(vis[sx]);
				if (delta > 0) {
					for (int x = 0; x < nx; x++) {
						if (vis[x])
							lx[x] -= delta;
					}
					for (int y = 0; y < ny; y++) {
						if (aug[y] > -1)
							ly[y] += delta;
						else
							slack[y].first -= delta;
					}
				}
//				assert(lx[sx] + ly[sy] == w[sx][sy]);
				aug[sy] = sx;
				sx = my[sy];
				if (sx == -1)
					break;
				vis[sx] = 1;
				for (int y = 0; y < ny; y++) {
					if (aug[y] == -1) {
						if (lx[sx]+ly[y]-w[sx][y] < slack[y].first)
							slack[y] = make_pair(lx[sx]+ly[y]-w[sx][y], sx);
					}
				}
			}
			
			while (sy != -1) {
				int sx = aug[sy];
				int ty = mx[sx];
				my[sy] = sx;
				mx[sx] = sy;
				sy = ty;
			}
		}
		
		int ret = 0;
		for (int i = 0; i < nx; i++)
			ret += lx[i];
		for (int i = 0; i < ny; i++)
			ret += ly[i];
		return ret;
	}
	void init(int nx, int ny) {
		this->nx = nx, this->ny = ny;
		for (int i = 0; i < nx; i++)
			w[i] = _mem + i*ny;
	}
} km;

int main() {
	int n, m;
	const int MAXN = 2005;
	int bx[MAXN], by[MAXN];
	int cx[MAXN], cy[MAXN];
	int sx, sy;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%d %d", &bx[i], &by[i]);
		for (int i = 0; i < m; i++)
			scanf("%d %d", &cx[i], &cy[i]);
		scanf("%d %d", &sx, &sy);
		km.init(n, m+(n-1));
		int ret = 0;
		for (int i = 0; i < n; i++) {
			int b = abs(bx[i]-sx)+abs(by[i]-sy);
			ret += b;
			for (int j = 0; j < m; j++) {
				int d = abs(bx[i]-cx[j])+abs(by[i]-cy[j]);
				km.w[i][j] = -d;
			}
			for (int j = 0; j < n-1; j++)
				km.w[i][j+m] = -b;
		}
		ret += -km.match();
		printf("%d\n", ret);
	}
	return 0;
}
/*
2 2
1 0
0 -1
-1 1
2 -1
0 0
*/
