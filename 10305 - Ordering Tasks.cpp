#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo 100000
int map[101][101], indeg[101], outdeg[101];
int n, m, x, y, i;
void TopologicalSort() {
	int i, j, degn;
	for(i = 0; i < n; i++) {
		for(j = 1; j <= n; j++) {
			if(indeg[j] == 0)
				break;
		}
		degn = j;
		if(i)	printf(" ");
		printf("%d", degn);
		indeg[degn] = -1;
		for(j = 0; j < outdeg[degn]; j++)
			indeg[map[degn][j]]--;
	}
	puts("");
}
int main() {
	while(scanf("%d %d", &n, &m) == 2) {
		if(n == 0 && m == 0)
			break;
		memset(indeg, 0, sizeof(indeg));
		memset(outdeg, 0, sizeof(outdeg));
		for(i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			map[x][outdeg[x]++] = y;
			indeg[y]++;
		}
		TopologicalSort();
	}
    return 0;
}
