#include<stdio.h>
main() {
	int n, A[101], sum, Ans, a;
	while(scanf("%d", &n) == 1) {
		for(a = 0, sum = 0; a < n; a++)
			scanf("%d", &A[a]), sum += A[a];
		sum /= n, Ans = 0;
		for(a = 0; a < n-1; a++)
			if(A[a] != sum) {
				A[a+1] += A[a] - sum;
				Ans++;
			}
		printf("%d\n", Ans);
	}
	return 0;
}
