#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	char ss[1024];
	int n, s, p;
	while (scanf("%s", &ss) == 1) {
		printf("%s\n", ss);
		if (!strcmp(ss, "TheEnd"))
			break;
		scanf("%d %d %d", &n, &s, &p);
		int g[26][26] = {};
		for (int i = 0; i < p; i++) {
			scanf("%s", ss);
			int x = ss[0] - 'A', y = ss[1] - 'A';
			g[x][y] = g[y][x] = 1;
		}
		int mask[26] = {};
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				mask[i] |= g[i][j]<<j;
		int ret = 0;
		for (int i = (1<<n)-1; i >= 0; i--) {
			if (__builtin_popcount(i) == s) {
				int ok = 1;
				for (int j = 0; j < n && ok; j++) {
					if ((i>>j)&1)	continue;
					if (__builtin_popcount(mask[j]&i) >= 2)
						ok = 0;
				}
				ret += ok;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
