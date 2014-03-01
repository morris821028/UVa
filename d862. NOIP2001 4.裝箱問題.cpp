#include<stdio.h>
main() {
	int V, n, x;
	while(scanf("%d %d", &V, &n) == 2) {
		int DP[20001] = {}, a, max = 0;
		while(n--) {
			scanf("%d", &x);
			for(a = V-x; a >= 0; a--)
				if(DP[a+x] <= DP[a] + x) 
					DP[a+x] = DP[a] + x; 
		} 
		for(a = 0; a <= V; a++) 
			max = (max > DP[a]) ? max : DP[a];
		printf("%d\n", V-max); 
	} 
	return 0; 
}

