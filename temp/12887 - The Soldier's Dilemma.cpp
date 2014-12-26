#include <stdio.h> 
/*
add tallest people in position i
ways[n] = \sum ways[i] * ways[n-i-1].
			   ^^^^^^[1] ^^^^^^^^^^[2]
[1] left tree pos[0, i-1]
[2] right tree pos[i+1, n-1]
then label of right tree must small than label of left tree
=> Catalan number, an = (4n-2)/(n+1) * an-1
*/
long long inv(long long n, long long m) { // get n*? = 1 (mod m)
	long long la = 1, lb = 0, ra = 0, rb = 1;
	long long i = 0, t, mod = m;
	while(n%m) {
		if(!i) {
			la -= n/m*ra, lb -= n/m*rb;
		} else {
			ra -= n/m*la, rb -= n/m*lb;
		}
		i = !i;
		t = n, n = m, m = t%m;
	}
	return i ? (la%mod+mod)%mod : (ra%mod+mod)%mod;
}
#define MAXN 5005
long long Catalan[MAXN];
const long long mod = 1000000007LL;
int main() {
	Catalan[0] = Catalan[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		Catalan[i] = Catalan[i-1] * (4 * i - 2) %mod;
		Catalan[i] = Catalan[i] * inv(i+1, mod) %mod;
	}
	int n, testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("%lld\n", Catalan[n]);
	}
	return 0;
}
