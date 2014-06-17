#include<stdio.h>
int time, n;
void DFS(int x) {
	int a, t = x/2;
	for(a = 1; a <= t; a++)
		DFS(a), time++;
} 
main() {
	while(scanf("%d", &n) == 1) {
		time = 1, DFS(n);
		printf("%d\n", time);
	}
	return 0;
}
