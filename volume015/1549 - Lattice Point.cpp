#include <bits/stdc++.h>
using namespace std;

int64_t lattice(int64_t r) {
	int64_t ret = 0;
	int64_t r2 = r*r;
	for (int64_t x = 0, y = r, x2 = 0, y2 = r*r; x <= r; x++) {
		while (x2+y2 > r2)
			y--, y2 -= (y<<1)+1;
		ret += y;
		x2 += (x<<1)+1;
	}
	return ret*4 + 1;
}

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%d\n%lld\n", n, lattice(n));
	}
	return 0;
}
/*
1
2
3
10000
100000000
*/
