#include<stdio.h>
main() {
	int a, b, c, n;
	while(scanf("%d %d", &c, &n) == 2) {
		int DP[1001] = {}, money[10];
		for(a = 0; a < n; a++)	scanf("%d", &money[a]);
		for(a = 0; a <= c; a++)
			for(b = 0; b < n; b++)
				if(a + money[b] <= c) {
					if(DP[a + money[b]] == 0) {
						if(a == 0)
							DP[a + money[b]] = 1;
						else
							DP[a + money[b]] = DP[a] + 1;
					}
					else if(DP[a + money[b]] > DP[a] + 1)
						DP[a + money[b]] = DP[a] + 1;
				}
		printf("%d\n", DP[c]);
	}
	return 0;
}
