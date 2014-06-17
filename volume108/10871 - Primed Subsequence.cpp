#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int Prime[5500], Pt;
void sieve() {
	Pt = 0;
	char mark[50000] = {};
	int i, j;
	for(i = 2; i < 50000; i++) {
		if(mark[i] == 0) {
			Prime[Pt++] = i;
			for(j = 2; i*j < 50000; j++)
				mark[i*j] = 1;
		}
	}
}
int judgePrime(int n) {
	static int i, sqr;
	sqr = (int)sqrt(n);
	for(i = 0; Prime[i] <= sqr && i < Pt; i++)
		if(n%Prime[i] == 0)
			return 0;
	return 1;
}
int main() {
	sieve();
	int t, n, i, j, k;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		int A[10000], B[10000];
		for(i = 0; i < n; i++) {
			scanf("%d", &A[i]);
			B[i] = A[i];
			if(i != 0)
				A[i] += A[i-1];
		}
		int flag = 0, tmp;
		for(i = 2; i <= n && !flag; i++) {
			for(j = 0; j <= n-i && !flag; j++) {
				if(j == 0)
					tmp = A[j+i-1];
				else
					tmp = A[j+i-1] - A[j-1];
				if(judgePrime(tmp) == 1) {
					printf("Shortest primed subsequence is length %d:", i);
					for(k = j; k < j+i; k++)
						printf(" %d", B[k]);
					flag = 1;
					puts("");
				}
			}
		}
		if(!flag)
			puts("This sequence is anti-primed.");
	}
    return 0;
}
