#include <stdio.h>
typedef unsigned long long ULL;
ULL gcd(ULL x, ULL y) {
	if(x == 0)	return y;
	if(y == 0)	return x;
	ULL tmp;
	while(x%y) {
		tmp = x, x = y, y = tmp%y;
	}
	return y;
}
int main() {
	ULL DP[25][151] = {}, total[25];
	int i, j, k, n, m;
	DP[0][0] = 1, total[0] = 1;
	for(i = 1; i <= 24; i++) {
		for(j = 6*i; j >= i; j--) {
			for(k = 1; k <= 6 && j-k >= 0; k++)
				DP[i][j] += DP[i-1][j-k];
		}
		total[i] = total[i-1]*6;
	}
	for(i = 1; i <= 24; i++) {
		for(j = 6*i; j >= 0; j--) {
			DP[i][j] += DP[i][j+1];
		}
	}
	while(scanf("%d %d", &n, &m) == 2) {
		if(n == 0 && m == 0)
			break;
		ULL x = DP[n][m], y = total[n];
		ULL GCD = gcd(x, y);
		x /= GCD;
		y /= GCD;
		if(y == 1)
			printf("%llu\n", x);
		else
			printf("%llu/%llu\n", x, y);
	}
    return 0;
}
