#include<stdio.h>
#include<string.h>
int main() {
    int T, N, P, R;
	long long DP[17][17][17];
	memset(DP, 0, sizeof(DP));
    DP[1][1][1] = 1;
    for(N = 2; N <= 13; N++)
        for(P = 1; P <= N; P++)
            for(R = 1; R <= N; R++)
                DP[N][P][R] = DP[N-1][P][R]*(N-2) + DP[N-1][P-1][R] + DP[N-1][P][R-1];
    scanf("%d", &T);
    while(T--) {
        scanf("%d %d %d", &N, &P, &R);
        printf("%lld\n", DP[N][P][R]);
    }
    return 0;
}
