#include<stdio.h>
#include<stdlib.h>
main() {
	int N, t[3] = {}, x; 
	scanf("%d", &N);
	while(N--) 
		scanf("%d", &x), t[x%3]++; 
	printf("%d %d %d\n", t[0], t[1], t[2]); 
	return 0; 
}
