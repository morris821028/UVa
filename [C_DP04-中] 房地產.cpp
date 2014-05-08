#include <stdio.h>
#include <algorithm>
int main() {
	scanf("%*d");
	for(int n; scanf("%d", &n) == 1;) {
		int g[105][105], used[105] = {}, ret, cost[105];
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < n; j++) 
				scanf("%d", &g[i][j]);
			cost[i] = 0x3f3f3f;
		}
		ret = 0, cost[0] = 0;
		for(int i = 0; i < n; i++) {
			int mn = 0x3f3f3f, mi;
			for(int j = 0; j < n; j++)
				if(cost[j] < mn && used[j] == 0)
					mn = cost[j], mi = j;
			ret += mn, used[mi] = 1;
			for(int j = 0; j < n; j++)
				if(g[mi][j])
					cost[j] = std::min(cost[j], g[mi][j]);
		}
		printf("%d\n", ret);
	}
	return 0;
}
