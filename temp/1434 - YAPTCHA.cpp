// math, Wilson's theorem, (p-1)! = -1 (mod p)
// http://en.wikipedia.org/wiki/Wilson%27s_theorem
#include <stdio.h>
#define MAXL (4194304>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
void sieve() {
	register int i, j, k;
	SET(1);
	int n = 4194304;
	for(i = 2; i <= n; i++) {
		if(!GET(i)) {
			for (k = n/i, j = i*k; k >= i; k--, j -= i)
				SET(j);
		}
	}
}
int S[1048576];
// if 3k+7 is not a prime, 3k+7 = a*b, then a, b <= 3k+6, 
// we get (3k+7) | (3k+6)!, so item = 0
// if 3k+7 is prime, (3k+7) | (3k+6)!+1 by Wilson's theorem
// so item = 1
int main() {
	sieve();
	for (int i = 1; i < 1048576; i++)
		S[i] = S[i-1] + (GET(3 * i + 7) == 0);
	
	int testcase, n; 
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("%d\n", S[n]);
	} 
	return 0;
}
