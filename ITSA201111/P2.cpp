#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
char map[20][20], s[150], flag;
int N, M, i, j;
void DFS(int x, int y, int index) {
	if(s[index] == '\0')	{flag = 1;return;}
	if(flag)	return;
	if(x < 0 || x >= N || y < 0 || y > N)	return;
	if(map[x][y] != s[index])	return;
	DFS(x+1, y, index+1);
	DFS(x-1, y, index+1);
	DFS(x, y+1, index+1);
	DFS(x, y-1, index+1);
}
main() {
	while(scanf("%d %d", &N, &M) == 2) {
		getchar();
		for(i = 0; i < N; i++) {
			scanf("%s", map[i]);
		}
		while(M--) {
			scanf("%s", s);
			flag = 0;
			for(i = 0; i < N; i++)
				for(j = 0; j < N; j++) {
					if(map[i][j] == s[0] && flag == 0) {
						DFS(i, j, 0);
					}
				}
			if(!flag)
				printf("No\n");
			else
				printf("Yes\n");
		}
	}
	return 0;
}
