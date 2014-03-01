#include<stdio.h>
#include<string.h>
int map[20][20] = {}, n;
char Way[20], Last[20], Ans[20000000], *At;
int next[20];
void DFS(int now, int set) {
	int a, pre = 0;
	if(now == 0) {
		for(a = 0; a < set; a++) {
			if(Way[a]-1+'A' != Last[a])
				Last[a] = Way[a]-1+'A', *At++ = Last[a];
		}
		*At++ = '\n';
		return;
	}
	for(a = next[0]; a; pre = a, a = next[a]) 
		if(!map[a][set]){
			next[pre] = next[a];
			Way[set] = a;
			DFS(now-1, set+1);
			next[pre] = a;
		}
}
main() {
    int a, x;
	while(scanf("%d", &n) == 1) {
		for(a = 0; a < n; a++)
			next[a] = a+1;
		memset(Last, 0, sizeof(Last));
		memset(map, 0, sizeof(map));
		At = Ans;
		for(a = 1; a <= n; a++) {
			while(scanf("%d", &x) == 1 && x != 0)
				map[a][x-1] = 1;
		}
		
		next[n] = 0;
		DFS(n, 0);
		*At = '\0', puts(Ans);
	}
	return 0;
}
