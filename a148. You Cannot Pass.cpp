#include<stdio.h>
main() {
	int a, n, x;
	while(scanf("%d", &n) == 1) {
		int sum = 0;
		for(a = 0; a < n; a++)
			scanf("%d", &x), sum += x;
		puts(n*59 >= sum ? "yes" : "no");
	}
	return 0;
}
