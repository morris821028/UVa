#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int map[105][105] = {}, mt[105] = {}, Ans;
int n, m, x, y, i, j;
void DFS(int now, int choose, int use) {
	if(use == m) {
		if(choose < Ans)	Ans = choose;
		return ;
	}
	if(now == n)	return;
	if(mt[now] != 0) {
		int i, sum = 0;
		for(i = 0; i < n; i++) {
			if(map[now][i] != 0) {
				map[i][now] = 0;
				sum += map[now][i];
				mt[i] -= map[now][i];
			}
		}
		DFS(now+1, choose+1, use+sum);
		for(i = 0; i < n; i++) {
			if(map[now][i] != 0) {
				map[i][now] = map[now][i];
				mt[i] += map[now][i];
			}
		}
		DFS(now+1, choose, use);
	} else {
		DFS(now+1, choose, use);
	}
}
int main() {
	while(scanf("%d %d", &m, &n) == 2) {
		memset(map, 0, sizeof(map));
		for(i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			map[x][y]++, map[y][x]++;
			mt[x]++, mt[y]++;
		}
		Ans = n;
		DFS(0, 0, 0);
		printf("%d\n", Ans);
		/*
		for(i = 0; i <= n; i++) {
			int maxdeg = 0, idx;
			for(j = 0; j < n; j++) {
				if(maxdeg < mt[j])
					maxdeg = mt[j], idx = j;
			}
			if(maxdeg == 0)	break;
			for(j = 0; j < n; j++) {
				if(map[idx][j] != 0) {
					map[j][idx] = 0;
					mt[j]--;
				}
			}
			mt[idx] = 0;
		}
		printf("%d\n", i);*/
	}
    return 0;
}
