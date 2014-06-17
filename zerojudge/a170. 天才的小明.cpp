#include<stdio.h>
main() {
	int t, x, y;
	scanf("%d", &t);
	while(t--) {
		scanf("%o %o", &x, &y);
		printf("%X\n", x+y);
	}
	return 0;
}
