#include<stdio.h>
#include<stdlib.h>
#include<math.h> 
main() {
	int a, b, t, i, j;
	scanf("%d", &t); 
	for(i = 1; i <= t; i++) { 
		scanf("%d %d", &a, &b); 
		int s = 0; 
		for(j = ceil(sqrt(a)); j*j <= b; j++) 
			s += j*j;
		printf("Case %d: %d\n", i, s); 
	} 
	return 0; 
}

