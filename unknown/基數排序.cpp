#include<stdio.h>
#define	MaxN 100001
void RadixSort(int *A, int *B, int n) {
	int a, x, d, *T, C[16];
	for(x = 0; x < 4; x++) {
		d = x*4;
		for(a = 0; a < 16; a++)		C[a] = 0;
		for(a = 0; a < n; a++)		C[(A[a]>>d)&15]++;
		for(a = 1; a < 16 ; a++)	C[a] += C[a-1];
		for(a = n-1; a >= 0; a--)	B[--C[(A[a]>>d)&15]] = A[a];
		T = A, A = B, B = T;
	}	
}
main() {
	int S0[MaxN], S1[MaxN];
	int n, a, l, r;
	while(scanf("%d %d %d", &n, &l, &r) == 3) {
		for(a = 0; a < n ; a++)	scanf("%d", &S0[a]);
		RadixSort(S0+l, S1, r-l+1);
		for(a = 0; a < n; a++)	printf("%d ", S0[a]);
		puts("");
	}
	return 0;
}
