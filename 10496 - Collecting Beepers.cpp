#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxState 1<<12
#define maxN 12
int DP[maxState][maxN], map[20][20];
int TSP(int state, int last, int n) {
	if(state == 0 && last != 0)	return 0xfffff;
	if(DP[state][last] != -1)	return DP[state][last];
	int i, min = 0xfffff, tmp;
	for(i = 0; i <= n; i++) {
		if((state&(1<<i)) != 0) {
			tmp = TSP(state-(1<<i), i, n);
			tmp += map[i][last];
			if(min > tmp)	min = tmp;
		}
	}
	DP[state][last] = min;
	return DP[state][last];
}
int main() {
	int T, x[20], y[20];
	int sizex, sizey, n, i, j;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &sizex, &sizey);
		scanf("%d %d", &x[0], &y[0]);
		scanf("%d", &n);
		for(i = 1; i <= n; i++)
			scanf("%d %d", &x[i], &y[i]);
		for(i = 0; i <= n; i++)
			for(j = 0; j <= n; j++)
				map[i][j] = abs(x[i]-x[j])+abs(y[i]-y[j]);
		memset(DP, -1, sizeof(DP));
		DP[0][0] = 0;
		printf("The shortest path has length %d\n", TSP((1<<(n+1))-1, 0, n));
	}
    return 0;
}
