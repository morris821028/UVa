#include<stdio.h>
#include<string.h>
#define oo 100000
int map[30][30], used[30], back[30], joint[30], chose[30];
int n, find, Ans;
int min(int x, int y) {
	return x < y ? x : y;
}
int DFS(int now, int last, int depth) {
	int a, back_depth = depth-1, t;
	back[now] = depth, find++;
	/*printf("now %d back %d\n", now, back[now]);*/
	for(a = 0; a <= n; a++) {
		if(map[now][a]) {
			if(used[a]) {
				back_depth = min(back_depth, back[a]);
			} else {
				used[a] = 1;
				t = DFS(a, now, depth+1);
				back_depth = min(back_depth, t);
			}
			/*printf("now -> back %d %d\n", now, a);*/
		}
	}
	if(back_depth == depth-1) {
		for(a = 0; a <= n; a++)
			if(map[now][a] && joint[a] == 1 && chose[a] == 1)
				break;
		if(a == n+1)	{Ans++;chose[now] = 1;}
		joint[now] = 1;
	}
	/*printf("now %d back_depth %d\n", now, back_depth);*/
	return back_depth;
}
main() {
	int x, y;
	while(scanf("%d", &n) == 1) {
		memset(map, 0, sizeof(map));
		memset(used, 0, sizeof(used));
		memset(chose, 0, sizeof(chose));
		memset(joint, 0, sizeof(joint));
		while(scanf("%d", &x) == 1 && x) {
			scanf("%d", &y);
			map[x][y] = 1, map[y][x] = 1;
		}
		Ans = 0, find = 0, used[1] = 1, DFS(1, 0, 0);
		printf("%d\n", Ans+(n-find));
	}
	return 0;
}
/*
5
1 2
1 4
2 3
3 4
4 5
0
test1
8
1 3
3 4
5 1
2 6
4 5
6 3
5 3
2 7
2 8
0
test2
24
1 2
1 3
1 4
1 5
1 6
1 7
1 8
1 9
1 10
1 11
11 12
test3
22
1 3
3 4
5 1
2 6
4 5
6 3
5 3
2 7
2 8
7 8
test4
8
1 3
3 4
5 1
2 6
4 5
6 3
5 3
2 7
2 8
7 8
4 7
0
test5
7
1 2
1 3
2 4
3 4
2 5
2 6
5 6
2 7
0
*/
