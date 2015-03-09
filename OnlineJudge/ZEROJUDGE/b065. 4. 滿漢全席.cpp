#include<stdio.h>
#include<stdlib.h>
struct Data{
	int like[2];
}judge[30];
int flag, n, m, Used[100] = {};
void DFS(int tn) {
	if(flag)	return;
	if(tn == n+1) {
		int a;
		for(a = 0; a < m; a++) {
			if(Used[judge[a].like[0]] == 0 && Used[judge[a].like[1]] == 0)
				break;
		}
		if(a == m)	flag = 1;
		return;
	}
	Used[tn*2] = 1;
	DFS(tn+1);
	Used[tn*2] = 0;

	Used[tn*2+1] = 1;
	DFS(tn+1);
	Used[tn*2+1] = 0;
}
main() {
	int k, a, b;
	char x[10], y[10];
	while(scanf("%d", &k) == 1) {
		while(k--) {
			scanf("%d %d", &n, &m);
			for(a = 0; a < m; a++) {
				scanf("%s %s", x, y);
				int t;
				for(b = 1, t = 0; x[b]; b++)	t = t*10 + x[b]-'0';
				judge[a].like[0] = t*2+(x[0] == 'h');
				for(b = 1, t = 0; y[b]; b++)	t = t*10 + y[b]-'0';
				judge[a].like[1] = t*2+(y[0] == 'h');
			}
			flag = 0, DFS(1);
			puts(flag ? "GOOD" : "BAD");
		}
	}
	return 0;
}
