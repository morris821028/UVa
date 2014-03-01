#include<stdio.h>
#include<stdlib.h>
main() {
	int T, n;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		int A[2][101] = {}, sum = 0, a, b, allsum;
		int D[2][101] = {};
		for(a = 1; a <= n; a++) {
			scanf("%d", &A[0][a]), sum += A[0][a];
			D[0][a] = D[0][a-1] + A[0][a];
		}
		for(a = 1; a <= n; a++) {
			scanf("%d", &A[1][a]), sum += A[1][a];
			D[1][a] = D[1][a-1] + A[1][a];
		}
		allsum = sum;
		sum /= 2;
		int tsum = 0, Ans1 = 0, Ans2 = allsum;
		tsum = 0;
		for(a = 1; a <= n; a++) {
			for(b = 0; b <= n; b++) {
				tsum = D[0][a] + D[1][b];
				if(Ans1 < tsum && tsum <= sum)	Ans1 = tsum;
				if(Ans2 > tsum && tsum >= sum)	Ans2 = tsum;
				if(a <= b) {
					tsum = allsum - (D[0][b] - D[0][a-1]);
					if(Ans1 < tsum && tsum <= sum)	Ans1 = tsum;
					if(Ans2 > tsum && tsum >= sum)	Ans2 = tsum;
				}
				if(a <= b) {
					tsum = allsum - (D[1][b] - D[1][a-1]);
					if(Ans1 < tsum && tsum <= sum)	Ans1 = tsum;
					if(Ans2 > tsum && tsum >= sum)	Ans2 = tsum;
				}
			}
		}
		printf("%d\n", Ans1 < Ans2 ? Ans1 : Ans2);
	}
	return 0;
}
/*
2
4
4 10 10 4
1 5 5 1 
*/
