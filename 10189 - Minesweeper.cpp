#include <stdio.h>
#include <string.h>
int table[201][201];
void add(int x, int y, int n, int m) {
	int i, dx, dy;
	int D[8][2] = {{1,0},{0,1},{-1,0},{0,-1},
					{1,1},{1,-1},{-1,1},{-1,-1}};
	for(i = 0; i < 8; i++) {
		dx = D[i][0], dy = D[i][1];
		if(x + dx >= 0 && x + dx < n && y + dy >= 0 && y + dy < m) {
			table[x+dx][y+dy]++;
		}
	}
}
int main() {
	int n, m, Case = 0, i, j;
	char map[201][201];
	while(scanf("%d %d", &n, &m) == 2) {
		if(n == 0 && m == 0)
			break;
		if(++Case != 1)	puts("");
		for(i = 0; i < n; i++)
			scanf("%s", &map[i]);
		memset(table, 0, sizeof(table));
		for(i = 0; i < n; i++) 
			for(j = 0; j < m; j++)
				if(map[i][j] == '*') {
					add(i, j, n, m);
				}
		printf("Field #%d:\n", Case);
		for(i = 0; i < n; i++, puts("")) {
			for(j = 0; j < m; j++)
				if(map[i][j] == '*')
					printf("*");
				else
					printf("%d", table[i][j]);
		}
	}
    return 0;
}
