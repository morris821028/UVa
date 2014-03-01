#include<stdio.h>
#include<string.h>
#include<time.h>
int map[20][20] = {}, n;
char Way[20], Last[20], Used[20] = {};
void DFS(int now, int set) {
	int a;
	if(now == 0) {
		for(a = 0; a < set; a++) {
			if(Way[a]-1+'A' != Last[a])
				Last[a] = Way[a]-1+'A', printf("%c", Last[a]);
		}
		puts("");
		return;
	}
	for(a = 1; a <= n; a++)
		if(!Used[a] && !map[a][set]) {
			Used[a] = 1;
			Way[set] = a;
			DFS(now-1, set+1);
			Used[a] = 0;
		}
}
main() {
    freopen("in.txt", "rt", stdin);  
    freopen("out.txt", "w+t", stdout);
    clock_t st, ed;
    st = clock();
	while(scanf("%d", &n) == 1) {
		memset(map, 0, sizeof(map));
		memset(Used, 0, sizeof(Used));
		memset(Last, 0, sizeof(Last));
		int a, x;
		for(a = 1; a <= n; a++) {
			while(scanf("%d", &x) == 1 && x != 0)
				map[a][x-1] = 1;
		}
		DFS(n, 0);
	}
    ed = clock();
    printf("%f\n", (float)(ed - st )/CLOCKS_PER_SEC);
	return 0;
}
