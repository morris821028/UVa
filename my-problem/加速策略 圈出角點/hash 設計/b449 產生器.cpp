#include <bits/stdc++.h>
using namespace std;
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
class ImageGenerator {
public:
	vector<unsigned long> mark;
	int n, m;
	ImageGenerator(int n = 1, int m = 1) {
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
};
int main() {
	int n, m, seed;
	while (scanf("%d %d %d", &n, &m, &seed) == 3) {
		ImageGenerator img(n, m), ans(n, m);
		img.rand_gen(seed);
		img.print();
		ans.set(3, 3);
		printf("%u\n", ans.signature());
	}
	return 0;
}
/*
7 7 8

*/
