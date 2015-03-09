#include<stdio.h>
main() {
	int n, a;
	while(scanf("%d", &n) == 1 && n) {
		for(a = 1; a < n; a++)	a%7 != 0 && printf("%d ", a);
		puts("");
	} 
	return 0;
}
