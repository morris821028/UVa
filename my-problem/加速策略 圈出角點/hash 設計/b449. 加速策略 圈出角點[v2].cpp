#include <bits/stdc++.h>
using namespace std;

const int dx[16] = {-3, -3, -2, -1, 0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3};
const int dy[16] = {0, 1, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3, -3, -3, -2, -1};
class Image {
public:
	vector<unsigned long> mark;
	int n, m;
	Image(int n = 1, int m = 1) {
		this->n = n, this->m = m;
		mark = vector<unsigned long>(((m*n)>>5)+1, 0);
	}
	void rand_gen(unsigned long seed) {
		unsigned long h = 2;
		for (int i = 0; i < mark.size(); i++) {
			h = hash(h + seed + i);
			mark[i] = h;
		}
	}
	inline int get(int x, int y) {
		x = x * m + y;
		return (mark[x>>5]>>(x&31))&1;
	}
	inline void set(int x, int y) {
		x = x * m + y;
		mark[x>>5] |= 1<<(x&31);
	}	
	int corner(int x, int y) {
		int c[4] = {get(x+dx[0], y+dy[0]), get(x+dx[4], y+dy[4]), 
				get(x+dx[8], y+dy[8]), get(x+dx[12], y+dy[12])};
		if (c[0] == c[1] && c[1] == c[2] || 
			c[1] == c[2] && c[2] == c[3] ||
			c[2] == c[3] && c[3] == c[0] ||
			c[3] == c[0] && c[0] == c[1]) {
			int cc = -1, p = 1;
			for (int it = 1, i = 1, j = 0; it < 16; it++, i++, i = i >= 16 ? 0 : i) {
				if (get(x+dx[i], y+dy[i]) == get(x+dx[j], y+dy[j]))
					j ++, j = j >= 16 ? 0 : j, p++;
				else {
					if (cc == -1)
						cc = p;
					j = i, p = 1;
				}
				if (p >= 12)
					return 1;
			}
			if (get(x+dx[0], y+dy[0]) == get(x+dx[15], y+dy[15]) && p+cc >= 12)
				return 1;
		}
		return 0;
	}
	void fetch(Image &store) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (i-3 >= 0 && j-3 >= 0 && i+3 < n && j+3 < m) {
					if (corner(i, j))
						store.set(i, j);
				}
			}
		}
	}
	void print() {
		printf("%d %d\n", n, m);
		for (int i = 0; i < n; i++, puts(""))
			for (int j = 0; j < m; j++)
				printf("%d", get(i, j));
	}
	unsigned long signature() {
		unsigned long h = 1;
		for (int i = 0; i < mark.size(); i++)
			h = hash(h + mark[i]);
		return h;
	}
private:
	unsigned long hash(unsigned long x) {
		return (x * 2654435761LU);
	}
} img, ans;
int main() {
	int n, m, seed;
	int cases = 0;
	while (scanf("%d %d %d", &n, &m, &seed) == 3) {
		img = Image(n, m);
		ans = Image(n, m);
		img.rand_gen(seed);
		img.fetch(ans);
//		img.print();
//		ans.print();
		printf("Case #%d: %u\n", ++cases, ans.signature());
	}
	return 0;
}
/*
7 7 8
20 20 16021
20 20 12856
*/
