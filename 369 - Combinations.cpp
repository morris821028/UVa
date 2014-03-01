#include<stdio.h>
int main() {
	int N, M, i, j;
	long long int PASCAL[101][101] = {0};
	PASCAL[1][0] = PASCAL[1][1] = 1;
	for(i = 2; i <= 100; i++) {
		PASCAL[i][0] = 1;
		for(j = 1; j < i; j++)
			PASCAL[i][j] = PASCAL[i-1][j] + PASCAL[i-1][j-1];
		PASCAL[i][i] = 1;
	}
	while(scanf("%d %d", &N, &M) == 2) {
		if(N == 0 && M == 0)
			break;
		printf("%d things taken %d at a time is %lld exactly.\n", N, M, PASCAL[N][M]);
	}
    return 0;
}
