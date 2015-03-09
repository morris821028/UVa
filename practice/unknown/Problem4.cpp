#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
main() {
	int n, map[30][30], i, j, k;
	while(scanf("%d", &n) == 1) {
		int sx, sy, ex, ey;		
		int Q[1000][2], Qt = 0, Ans[30][30];	
		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%d", &map[i][j]), Ans[i][j] = map[i][j];
		int DP[30][30], Used[30][30];
		int D[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
		int flag = 0;
		memset(DP, 0, sizeof(DP));
		memset(Used, -1, sizeof(Used));
		Q[0][0] = sx, Q[0][1] = sy;
		DP[sx][sy] = 0, Used[sx][sy] = 1;
		for(i = 0; i <= Qt && flag == 0; i++) {
			int x = Q[i][0], y = Q[i][1];
			for(j = 0; j < 4 && flag == 0; j++) {
				if(x+D[j][0] >= 0 && x+D[j][0] < n && y+D[j][1] >= 0 && y+D[j][1] < n && Used[x+D[j][0]][y+D[j][1]] == -1 && map[x+D[j][0]][y+D[j][1]] == 0) {
					DP[x+D[j][0]][y+D[j][1]] = DP[x][y]+1;
					Used[x+D[j][0]][y+D[j][1]] = 1;
					++Qt, Q[Qt][0] = x+D[j][0], Q[Qt][1] = y+D[j][1];
				}
				if(x+D[j][0] >= 0 && x+D[j][0] < n && y+D[j][1] >= 0 && y+D[j][1] < n && Used[x+D[j][0]][y+D[j][1]] == -1 && map[x+D[j][0]][y+D[j][1]] == 1) {
					flag = 1;
				/*	x = x+D[j][0], y = y+D[j][1];*/
					while(DP[x][y] != 0) {
						for(k = 0; k < 4; k++)
							if(DP[x][y]-1 == DP[x+D[k][0]][y+D[k][1]]) {
								Ans[x][y] = -1;
								x = x+D[k][0], y = y+D[k][1];
								break;
							}
					}
					int a, b;
					for(a = 0; a < n; a++) {
						for(b = 0; b < n; b++) {
							if(a == sx && b == sy)
								printf("X");
							else if(Ans[a][b] == -1)
								printf("*");
							else
								printf("%d", Ans[a][b]);
							if(b != n-1)
								printf(" ");
						}
						printf("\n");
					}
				}
			}
		}
		puts("");
		flag = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				Ans[i][j] = map[i][j];
		memset(DP, 0, sizeof(DP));
		memset(Used, -1, sizeof(Used));
		Q[0][0] = ex, Q[0][1] = ey, Qt = 0;
		DP[ex][ey] = 0, Used[ex][ey] = 1;
		for(i = 0; i <= Qt && flag == 0; i++) {
			int x = Q[i][0], y = Q[i][1];
			for(j = 0; j < 4 && flag == 0; j++) {
				if(x+D[j][0] >= 0 && x+D[j][0] < n && y+D[j][1] >= 0 && y+D[j][1] < n && Used[x+D[j][0]][y+D[j][1]] == -1 && map[x+D[j][0]][y+D[j][1]] == 0) {
					DP[x+D[j][0]][y+D[j][1]] = DP[x][y]+1;
					Used[x+D[j][0]][y+D[j][1]] = 1;
					++Qt, Q[Qt][0] = x+D[j][0], Q[Qt][1] = y+D[j][1];
				}
				if(x+D[j][0] >= 0 && x+D[j][0] < n && y+D[j][1] >= 0 && y+D[j][1] < n && Used[x+D[j][0]][y+D[j][1]] == -1 && map[x+D[j][0]][y+D[j][1]] == 1) {
					flag = 1;
					while(DP[x][y] != 0) {
						for(k = 0; k < 4; k++)
							if(DP[x][y]-1 == DP[x+D[k][0]][y+D[k][1]]) {
								Ans[x][y] = -1;
								x = x+D[k][0], y = y+D[k][1];
								break;
							}
					}
					int a, b;
					for(a = 0; a < n; a++) {
						for(b = 0; b < n; b++) {
							if(a == sx && b == sy)
								printf("X");
							else if(a == ex && b == ey)
								printf("Y");
							else if(Ans[a][b] == -1)
								printf("*");
							else
								printf("%d", Ans[a][b]);
							if(b != n-1)
								printf(" ");
						}
						printf("\n");
					}
				}
			}
		}
	}
	return 0;
}
/*
6
0 1
5 1
9 0 9 9 9 9
9 0 0 0 0 9
9 9 0 9 0 9
9 9 0 9 0 9
9 0 0 9 1 9
9 0 9 9 9 9
*/
