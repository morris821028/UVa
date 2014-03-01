#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int flag, Used[5], way[5];
int map[4][5];
void DFS(int now) {
	int i;
	if(now == 4) {
		if(flag == 0)	puts("ABCD");
		flag = 1;
		for(i = 0; i < 4; i++)
			printf("%d", way[i]);
		puts("");
		return;
	}
	for(i = 1; i <= 4; i++)
		if(Used[i] == 0 && map[now][i] == 0) {
			Used[i] = 1;
			way[now] = i;
			DFS(now+1);
			Used[i] = 0;
		}
}
main() {
	int N, x, i;
	char s[10];
	scanf("%d", &N);
	while(N--) {
		memset(map, 0, sizeof(map));
		memset(Used, 0, sizeof(Used));
		for(i = 0; i < 4; i++) {
			scanf("%s", s);
			while(scanf("%d", &x) == 1 && x) {
				map[s[0]-'A'][x] = 1; /*can't*/
			}
		}
		flag = 0;
		DFS(0);
		if(!flag)
			printf("No Solution\n");
		if(N)	puts("");
	}
	return 0;
}
