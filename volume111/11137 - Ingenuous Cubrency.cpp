#include <stdio.h>
int main() {
	int i, j, N;
	long long DP[10000] = {};
	DP[0] = 1;
	for(i = 1; i*i*i < 10000; i++) {
		for(j = i*i*i; j < 10000; j++)
			DP[j] += DP[j-i*i*i];
	}
	while(scanf("%d", &N) == 1) {
		printf("%lld\n", DP[N]);
	}
    return 0;
}
