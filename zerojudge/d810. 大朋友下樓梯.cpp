#include<stdio.h>
#include<stdlib.h>
main() {
	int a, b, c;
	int DP[4][20] = {}; 
	DP[1][1] = 1, DP[2][0] = 1, DP[2][1] = 1, DP[3][0] = 1, DP[3][1] = 1; 
	for(a = 1; a < 4; a++) 
		for(b = 2; b < 20; b++) 
			for(c = 1; c <= a && b-c >= 0; c++) 
				DP[a][b] += DP[a][b-c]; 
	while(scanf("%d %d", &a, &b) == 2)
		printf("%d\n", DP[a][abs(b)]); 
	return 0; 
}
