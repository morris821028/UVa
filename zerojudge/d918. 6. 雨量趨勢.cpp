#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int A[3500];
int Approximate_LIS(int E, int n) {
	int Ans = 0, i, j, tmp, DP[3500], max;
	memset(DP, 0, sizeof(DP));
	for(i = 0; i < n; i++) {
		tmp = 0, max = 0;
		for(j = i+1; j < n; j++) {			
			if(A[i]-E <= A[j] && A[j] < A[i])
				tmp++;
			if(A[i] <= A[j])
				DP[j] = DP[j] > DP[i]+tmp+1 ? DP[j] : (DP[i]+tmp+1);
			max = max > DP[j] ? max : DP[j];
		}
		Ans = Ans > DP[i]+tmp ? Ans : DP[i]+tmp;
	}
	return Ans+1;
}
main() {
	int n, m, i, E;
	while(scanf("%d %d", &n, &m) == 2) {
		for(i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for(i = 0; i < m; i++) {
			scanf("%d", &E);
			printf("%d ", Approximate_LIS(E, n));
		}
		puts("");
	}
	return 0;
}
