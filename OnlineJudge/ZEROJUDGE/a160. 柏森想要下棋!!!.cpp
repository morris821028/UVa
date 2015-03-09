#include<stdio.h>
#include<stdlib.h>
int n, row[13] = {}, map[13][13] = {};
int	s[13], time;
int check(int x, int y) {
	int a;
	for(a = 0; a < x; a++)
		if(abs(x-a) == abs(y-s[a])) return 0;
	return 1;
}
int Print() {
	int a, b;
	for(a = 0; a < n; a++, puts(""))
		for(b = 0; b < n; b++)
			printf("%c", map[a][b] ? 'Q': 'x');
	puts("");
}
void DFS(int now) {
	if(now == n) {
		time++, Print();
		return;
	}
	int a;
	for(a = 0; a < n; a++)
		if(row[a] == 0 && check(now, a) == 1) {
			row[a] = 1,	map[now][a] = 1, s[now] = a;
			DFS(now+1);
			row[a] = 0, map[now][a] = 0;
		}
}
main() {
	while(scanf("%d", &n) == 1 && n)
		time = 0, DFS(0), printf("%d\n", time);
	return 0;
}
