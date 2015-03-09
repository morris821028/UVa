#include<stdio.h>
#include<stdlib.h>
char type[5][2][5] = {
	{"*   ","*** "},{"    ","****"},
	{"  * ","*** "},{"**  ","**  "},
	{"*** "," *  "}};
char way[6], Used[6];
int Sum;
void DFS(int index, int n) {
	int a;
	if(index == n) {
		Sum++;
		for(a = 0; a < n; a++)	printf("%s|", type[way[a]][0]);
		puts("");
		for(a = 0; a < n; a++)	printf("%s|", type[way[a]][1]);
		printf("\n\n\n");
		return;
	}
	for(a = 0; a < 5; a++) {
		if((index == 0 || way[index-1] != a) && Used[a] != 0)
			way[index] = a, Used[a]--, DFS(index+1, n), Used[a]++;
	}
}
main() {
	int n, m, a;
	while(scanf("%d %d", &n, &m) == 2) {
		if(n == 0 && m == 0)	break;
		for(a = 0; a < 5; a++)	Used[a] = m;
		Sum = 0, DFS(0, n);
		printf("Sum : %d\n", Sum);
	}
	return 0;
}
