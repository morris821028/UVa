#include <bits/stdc++.h> 
using namespace std;

const int MAXV = 605;
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
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m, e;
		scanf("%d %d %d", &n, &m, &e);
		km.init(n, m);
		const int INF = 0x3f3f3f3f;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				km.w[i][j] = -INF; 
		}
		for (int i = 0; i < e; i++) {
			int u, v, c;
			scanf("%d %d %d", &u, &v, &c);
			km.w[u][v] = -c;
		}
		
		int ret = -km.match();
		printf("%d\n", ret);
		if (testcase)
			puts("");
	}
	return 0;
}
/*
2
4  5
9
0  2  5
0  3  3
1  1  20
1  4  10
2  1  25
2  4  30
3  0  2
3  2  10
3  3  12

3  3
9
0  0  3
0  1  2
0  2  1
1  0  1
1  1  7
1  2  9
2  0  3
2  1  7
2  2  5
*/
