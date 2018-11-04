#include <stdio.h>
#include "findLength.h"

#define MAXN 256
int main() {
	static int g[MAXN][MAXN];
    int n;
    int dx[] = {1, 1, 0, -1};
    int dy[] = {0, 1, 1, 1};
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++)
    		scanf("%d", &g[i][j]);
	}

	int len = 0;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < 4; j++) {
			cnt = findLength(g, n, 0, i, dx[j], dy[j]);
			if (cnt > len)
				len = cnt;
			cnt = findLength(g, n, i, 0, dx[j], dy[j]);
			if (cnt > len)
				len = cnt;
		}
	}
	printf("%d\n", len);
	return 0;
}
