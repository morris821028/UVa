#include<stdio.h>
#define limit 1500
#define Mod 1000000000
long long DP[1501][1501] = {}, Ans[1501] = {};
long long Sum[1501] = {};
main() {
	int a, b, c, d;
	DP[0][0] = 1;
	for(a = 1; a <= limit; a++) {
		for(b = 1; b <= a; b++) {
			DP[a][b] = (DP[a-1][b-1] + Sum[b])%Mod;
			Sum[b] = (Sum[b] - DP[a-b][b] + DP[a][b])%Mod; 
			Ans[a] = (Ans[a] + DP[a][b])%Mod;
		}
	}
	int n;
	while(scanf("%d", &n) == 1) {
		n /= 2;
		if(n >= 48)
			printf("%09lld\n", Ans[n]);
		else
			printf("%lld\n", Ans[n]);
	}
	return 0;
}
