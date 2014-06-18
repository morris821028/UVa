#include <stdio.h>
#include <string.h>
long long DP[34][34][100];
int main() {
	int t, n, k;
	int i, j, l, Case = 0;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &k);
		printf("Case %d: ", ++Case);
		if(n&1 || k == 0) {
			puts("0");
			continue;
		}
		memset(DP, 0, sizeof(DP));
		/*[zeros][ones][mod];*/
		DP[0][1][1%k] = 1;
		n /= 2;
		for(i = 0; i <= n; i++) {
			for(j = 0; j <= n; j++) {
				for(l = 0; l < k; l++) {
					DP[i+1][j][(l<<1)%k] += DP[i][j][l];
					DP[i][j+1][((l<<1)+1)%k] += DP[i][j][l];
				}
			}
		}
		printf("%lld\n", DP[n][n][0]);
	}
    return 0;
}
