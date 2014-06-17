#include <stdio.h>
#include <string.h>
int map[101][101], mt[101];
int tmp[101], Ans[101], maxL;
int cant[101];
int T, n, m;
void DFS(int node, int choose, int notchoose) {
	if(choose + notchoose == n || node == n+1) {	
		if(choose > maxL) {
			maxL = choose;
			int i;
			for(i = 0; i < maxL; i++)
				Ans[i] = tmp[i];
		}
		return;
	}		

	if(cant[node] == 0) {
		int i, newNot = notchoose;
		int reduce[n], idx = 0;
		for(i = 0; i < mt[node]; i++) {
			if(cant[map[node][i]] == 0) {
				cant[map[node][i]] = 1, newNot++;
				reduce[idx++] = map[node][i];
			}
		}
		tmp[choose] = node;
		DFS(node+1, choose+1, newNot);
		for(i = 0; i < idx; i++)
			cant[reduce[i]] = 0;
	}
	DFS(node+1, choose, notchoose+(!cant[node]));
}
int main() {
	int i, x, y;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		memset(mt, 0, sizeof(mt));
		memset(cant, 0, sizeof(mt));
		for(i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			map[x][mt[x]++] = y;
			map[y][mt[y]++] = x;
		}
		maxL = 0;
		DFS(1, 0, 0);
		printf("%d\n", maxL);
		for(i = 0; i < maxL-1; i++)
			printf("%d ", Ans[i]);
		printf("%d\n", Ans[i]);
	}
    return 0;
}
