#include<stdio.h>
main() {
	char A[33], B[33];
	while(scanf("%s %s", A, B) == 2) {
		int a, b, S[33] = {};
		printf("%s\n%s\n", A, B);
		puts("---------------------------------");
		for(a = 31; a >= 0; a--) {
			S[a] += A[a] + B[a] - 2 * '0';
			if(S[a] >= 2) S[a-1] += S[a]/2, S[a] %= 2;
		}
		for(a = 0; a <= 31; a++)
			printf("%d", S[a]);
		puts("");
		puts("****End of Data******************");
	}
	return 0;
}
