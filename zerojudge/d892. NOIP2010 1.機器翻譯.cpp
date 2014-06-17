#include<stdio.h>
main() {
	int n, m;
	while(scanf("%d %d", &m, &n) == 2) {
		int a, x, Ans = 0;
		int Used[1001] = {}, Q[1001], head = -1, tail = -1;
		for(a = 0; a < n; a++) {
			scanf("%d", &x);
			if(Used[x] == 0) {
				Ans++, Used[x] = 1;
				Q[++tail] = x;
				if(tail - head > m) Used[Q[++head]] = 0;
			} 
		}
		printf("%d\n", Ans); 
	}
	return 0;
}
