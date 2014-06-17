#include<stdio.h>
main() {
	int n, m;
	while(scanf("%d %d", &n, &m) == 2) {
		int sum = n, i;
		for(i = 1; sum <= m; sum+=i+n, i++);
		printf("%d\n", i);
	}
	return 0;
}
