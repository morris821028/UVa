#include<stdlib.h>
#include<stdio.h>
main() {  
	int N, M;
	while(scanf("%d %d", &N, &M) == 2) {
		N&1 && M&1 && printf("%d\n", (M-N)/2);
		N&1 && !(M&1) &&  printf("%d\n", (M-1-N)/2+1);
		!(N&1) && M&1 &&  printf("%d\n", (M-N)/2+1);
		!(N&1) && !(M&1) && printf("%d\n",(M-N)/2+1);
	} 
	return 0;
}
