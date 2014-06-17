#include <stdio.h>

int main() {
	long long C[201][201] = {0};
	int N, K;
	C[0][0] = 1;
	for(N = 1; N <= 200; N++) {
		C[N][0] = 1;
		for(K = 1; K <= N; K++)
			C[N][K] = (C[N-1][K-1] + C[N-1][K])%1000000;
	}
	while(scanf("%d %d", &N, &K) == 2) {
		if(N == 0 && K == 0)
			break;
		printf("%lld\n", C[N+K-1][K-1]);
	}
    return 0;
}
