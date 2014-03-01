#include <stdio.h>
#define oo 10000
int main() {
	int t, N, i, j;
	scanf("%d", &t);
	long long DP[10001] = {};
	DP[0] = 0;
	for(i = 1; i <= 10000; i++)	DP[i] = oo;
	for(i = 1; i <= 100; i++) {
		for(j = i*i; j <= 10000; j++)
			DP[j] = DP[j] < DP[j-i*i]+1 ? DP[j] : DP[j-i*i]+1;
	}
	while(t--) {
		scanf("%d", &N);
		printf("%lld\n", DP[N]);
	}
    return 0;
}
