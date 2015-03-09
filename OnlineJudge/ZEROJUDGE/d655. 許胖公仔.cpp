#include<stdio.h>
main() {
	int N, a, b, DP[1000] = {}, T;
	int money[9] = {30,70,110,1,5,10,50,100,500};
	for(a = 0; a < 1000; a++)
		for(b = 0; b < 9; b++)
			if(a + money[b] < 1000) {
				if(DP[a + money[b]] == 0) {
					if(a == 0)
						DP[a + money[b]] = 1;
					else
						DP[a + money[b]] = DP[a] + 1;
				}
				else if(DP[a + money[b]] > DP[a] + 1)
					DP[a + money[b]] = DP[a] + 1;
			}
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &N);
		printf("%d\n", N/1000 + DP[N%1000]);
	}
	return 0;
}
