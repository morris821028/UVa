#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int map[31][31], mt[31], max, mark[31][31];
int Used[31];
void DFS(int now, int L) {
	int i;
	for(i = 0; i < mt[now]; i++) {
		if(Used[map[now][i]] == 0 && mark[now][map[now][i]] == 0) {
			if(map[now][i] == 0) {
				if(L > max)	max = L;
				continue;
			}
			Used[map[now][i]] = 1;
			mark[now][map[now][i]] = 1;
			mark[map[now][i]][now] = 1;
			
			DFS(map[now][i], L+1);
			mark[now][map[now][i]] = 0;
			mark[map[now][i]][now] = 0;
			Used[map[now][i]] = 0;
		}
	}
}
int main() {
	int n, m, i, j, x, y;
	while(scanf("%d %d", &n, &m) == 2) {
		for(i = 0; i < n; i++)	mt[i] = 0, Used[i] = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				mark[i][j] = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			map[x][mt[x]++] = y;
			map[y][mt[y]++] = x;
		}
		max = 0;
		DFS(0, 0);
		printf("%d\n", max);
	}
    return 0;
}/*
2 1
0 1
6 7
0 1
0 2
1 2
1 3
2 5
3 4
4 5
*/
