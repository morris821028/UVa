#include<stdio.h>
#include<stdlib.h>
main() {
	char S[8], a;
	while(scanf("%s", &S) == 1) {
		for(a = 1; S[a]; a++) 
			printf("%d", abs(S[a] - S[a-1])); 
		puts(""); 
	} 
	return 0; 
}
