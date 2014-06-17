#include<stdio.h>
int DP[7001] = {}; 
void Sieve_DP() {
	DP[1] = 1; 
	int a, b; 
	char mark[7001] = {}; 
	for(a = 2; a <= 7000; a++) {
		DP[a] = DP[a-1]; 
		if(mark[a] == 0) {
			for(b = 2; a*b<= 7000; b++)
				mark[a*b] = 1; 
		} 
		else DP[a] += a; 
	} 
} 
main() {
	Sieve_DP(); 
	int A, B, T; 
	scanf("%d", &T); 
	while(T--) {
		scanf("%d %d", &A, &B); 
		printf("%d\n", DP[B] - DP[A-1]); 
	} 
	return 0; 
}
