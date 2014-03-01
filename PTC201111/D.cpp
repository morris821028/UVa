#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int main() {
	int T, n, m, i, j, A[60];
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		scanf("%d", &m);
		int DP[9001];
		memset(DP, 0, sizeof(DP));
		DP[0] = 1;
		for(i = 0; i < n; i++) {
			for(j = m; j >= A[i]; j--) {
				DP[j] += DP[j-A[i]];
			}
		}
		printf("%d\n", DP[m]*1000);
	}
	return 0;
}
