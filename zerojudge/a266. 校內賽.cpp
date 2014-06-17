#include<stdio.h>
#include<string.h>
int main() {
	int n, m, i, j, k, x, y;
	int map[101][101], mt[101];
	int inp[101][101], it[101];
	while(scanf("%d %d", &n, &m) == 2) {		
		int Q[101], Qt, Used[101], tn;
		int flag = 0;
		memset(mt, 0, sizeof(mt));
		memset(it, 0, sizeof(it));
		for(i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			map[x][mt[x]++] = y;
			inp[y][it[y]++] = x;
		}		
		memset(Used, 0, sizeof(Used));
		for(i = 1;  i <= n; i++) {
			Qt = 0, Q[Qt] = i;
			memset(Used, 0, sizeof(Used));
			for(j = 0; j <= Qt; j++) {
				tn = Q[j];
				for(k = 0; k < mt[tn]; k++)
					if(Used[map[tn][k]] == 0)
						Q[++Qt] = map[tn][k], Used[map[tn][k]] = 1;
			}
			x = Qt;
			Qt = 0, Q[Qt] = i;
			memset(Used, 0, sizeof(Used));
			for(j = 0; j <= Qt; j++) {
				tn = Q[j];
				for(k = 0; k < it[tn]; k++)
					if(Used[inp[tn][k]] == 0)
						Q[++Qt] = inp[tn][k], Used[inp[tn][k]] = 1;
			}
			y = Qt;
			if(x+y == n-1)
				printf("%d ", i), flag = 1;
		}
		if(!flag)	printf("non");
		puts("");
	}
	return 0;
}
