#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	int n, st, Case = 0, x, y, i, j;
	while(scanf("%d", &n) == 1 && n) {
		scanf("%d", &st);
		int map[101][101] = {};
		while(scanf("%d %d", &x, &y) == 2) {
			if(x == 0 && y == 0)
				break;
			map[x][y] = 1;
		}
		int Queue[10000], idx = -1;
		int Used[101] = {}, V[101] = {}, tn;
		Queue[++idx] = st, Used[st] = 1;
		for(i = 0; i <= idx; i++) {
			tn = Queue[i];
			Used[tn] = 0;
			for(j = 1; j <= n; j++) {
				if(map[tn][j] != 0 && V[tn]+1 > V[j]) {
					V[j] = V[tn]+1;
					if(Used[j] == 0)
						Queue[++idx] = j, Used[j] = 1;
				}
			}
		}
		int length = 0, ed = st;
		for(i = 1; i <= n; i++) {
			if(V[i] > length)
				length = V[i], ed = i;
		}
		printf("Case %d: The longest path from %d has length %d, finishing at %d.\n\n", ++Case, st, length, ed);
	}
    return 0;
}
