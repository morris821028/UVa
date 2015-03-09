#include<stdio.h>
main() {
	int n, m;
	while(scanf("%d %d", &n, &m) == 2) {
		if(n == m) puts("= =\""); 
		else puts(">\\\\\\<"); 
	} 
	return 0; 
}
