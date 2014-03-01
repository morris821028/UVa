#include <stdio.h>
#include <string.h>

long long A[201], DP[201][16][21];
void solve(int N, int M, int D) {
	memset(DP, 0, sizeof(DP));
	int i, j, k;
	long long tmp;
	DP[0][0][0] = 1;
	for(i = 1; i <= N; i++) {
		for(j = 0; j <= M; j++) {
			for(k = 0; k < D; k++) {
				tmp = (k+A[i])%D;
				if(tmp < 0) tmp += D;
				DP[i][j][k] += DP[i-1][j][k];
				if(j) {
					DP[i][j][k] += DP[i-1][j-1][tmp];
				}
			}
		}
	}
	printf("%lld\n", DP[N][M][0]);
}
int main() {
	int N, Q, D, M, i;
	int Case = 0;
	while(scanf("%d %d", &N, &Q) == 2) {
		if(N == 0 && Q == 0)	break;
		for(i = 1; i <= N; i++)
			scanf("%lld", &A[i]);
		printf("SET %d:\n", ++Case);
		for(i = 1; i <= Q; i++) {
			scanf("%d %d", &D, &M);
			printf("QUERY %d: ", i);
			solve(N, M, D);
		}
	}
    return 0;
}
