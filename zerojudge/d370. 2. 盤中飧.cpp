#include<stdio.h>
#include<math.h>
main() {
	int t, x, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &x, &k);
		int i, j, DP[20001] = {1, 0}, Ans;
		for(i = 2; i < k; i++)
			DP[i] = !(DP[i-1]);
		for(i = 1; i <= 20000; i++) {
			for(j = 1; j <= k; j += k-1)
				if(i+j >= k && i+j <= 20000)
					DP[i+j] |= !(DP[i]);
		}
		for(i = x+1; i <= 20000; i++)
			if(DP[i] == 0)
				break;
		if(i-x >= 10001)
			puts("0");
		else
			printf("%d\n", i-x);
	}
	return 0;
}
