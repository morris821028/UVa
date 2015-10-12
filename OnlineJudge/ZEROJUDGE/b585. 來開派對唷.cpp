#include <bits/stdc++.h> 
using namespace std;
int main() {
	int n, x;
	while (scanf("%d", &n) == 1 && n) {
		int g[32] = {}, ig[32] = {};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &x);
				if (i == j)
					continue;
				g[i] |= x<<j;
				ig[i] |= (1-x)<<j;
			}
		}
		int invalid[32] = {};
		while (true) {
			int ok = 1;
			for (int i = 0; i < n; i++) {
				if (invalid[i])	continue;
				int a = __builtin_popcount(g[i]);
				int b = __builtin_popcount(ig[i]);
				if (a < 2 || b < 2) {
					invalid[i] = 1;
					ok = 0;
					for (int j = 0; j < n; j++) {
						if (invalid[j])	continue;
						if ((g[j]>>i)&1)	g[j] ^= 1<<i;
						if ((ig[j]>>i)&1)	ig[j] ^= 1<<i;
					}
					break;
				}
			}
			if (ok)	break;
		}
		int ret = 0;
		for (int i = 0; i < n; i++)
			ret += invalid[i] == 0;
		printf("%d\n", ret);
	}
	return 0;
}
