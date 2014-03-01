#include<stdio.h>
char s[20000];
main() {
	int n, m, a, b, c;
	while(scanf("%d %d", &n, &m) == 2) {
		if(n == 0 && m == 0) break;
		int DP1[5001] = {}, DP2[5001] = {};
		int *A = DP1, *B = DP2, *C, Ans = 0;
		getchar();
		int L = 2*m-1;
		for(a = 0; a < n; a++) {
			gets(s);
			for(b = 0, c = 1; b < L; b += 2, c++) {
				if(s[b] != '2') {
					B[c] = A[c];
					B[c] = B[c] < A[c-1] ? B[c] : A[c-1];
					B[c] = B[c] < B[c-1] ? B[c] : B[c-1];
					B[c]++;
					Ans = Ans > B[c] ? Ans : B[c];
				}
				else {B[c] = 0;}
			}
			C = A, A = B, B= C;
		}
		printf("%d\n", Ans*Ans);
	} 
	return 0;
}
