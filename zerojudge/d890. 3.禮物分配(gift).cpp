#include<stdio.h>
main() {
	int n, k, a, b, A[500];
	while(scanf("%d %d", &n, &k) == 2)  {
		int DP[50001] = {}, sum = 0, half; 
		for(a = 0; a < n; a++) 
			scanf("%d", &A[a]), sum += A[a];
		half = sum /2;
		for(a = 0; a < n; a++) 
			for(b = half - A[a]; b >= 0; b--) 
				if(DP[b+A[a]] <= DP[b] + A[a]) 
					DP[b+A[a]] = DP[b] + A[a];
		int max = 0;
		for(a = 0; a <= half; a++) 
			max = (max > DP[a]) ? max : DP[a];
		if(max < sum - max) 
			printf("%d %d\n", max, sum - max);
		else
			printf("%d %d\n", sum - max, max); 
	}
	return 0; 
}
