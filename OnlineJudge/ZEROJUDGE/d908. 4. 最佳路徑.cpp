#include<stdio.h>
char s[2], x[2], y[2];
int n, a, Map[26][26] = {}, d, max;
int Used[26] = {};
void DFS(int now, int sum) {
	int a;
	if(sum > max) max = sum;
	for(a = 0; a < 26; a++) {
		if(Map[now][a] != 0 && Used[a] == 0)
			Used[a] = 1, DFS(a, sum + Map[now][a]), Used[a] = 0;
	}
}
main() {
	scanf("%s", s); {
		scanf("%d", &n);
		for(a = 0; a < n; a++) {
			scanf("%s %s %d", x, y, &d);
			Map[x[0]-'A'][y[0]-'A'] = Map[x[0]-'A'][y[0]-'A'] > d ? Map[x[0]-'A'][y[0]-'A'] : d;
		}
		max = 0;
		DFS(s[0] - 'A' , 0);
		printf("%d\n", max);
	}
	return 0;
}
