#include<stdio.h>
#include<string.h>
#define oo 0xffff
int main() {
	int n, x, y, i, j, k, m;
	int map[101][101];
	while(scanf("%d", &n) == 1 && n) {
		memset(map, 0, sizeof(map));
		while(scanf("%d", &x) == 1 && x) {
			while(scanf("%d", &y) == 1 && y)
				map[x][y] = 1;
		}
		for(i = 1; i <= n; i++)
			for(j = 1; j <= n; j++)
				if(map[i][j] == 0)
					map[i][j] = oo;
		for(k = 1; k <= n; k++)
			for(i = 1; i <= n; i++)
				for(j = 1; j <= n; j++)
					if(map[i][j] > map[i][k] + map[k][j])
						map[i][j] = map[i][k] + map[k][j];
		scanf("%d", &m);
		while(m--) {
			scanf("%d", &x);
			int Ans[101], At = 0;
			for(i = 1; i <= n; i++)
				if(map[x][i] == oo)
					Ans[At++] = i;
			printf("%d", At);
			for(i = 0; i < At; i++)
				printf(" %d", Ans[i]);
			puts("");
		}
	}
    return 0;
}
