#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 1e9+7;
const int MAXN = 1000005;
int64_t f[MAXN], r[MAXN];
/* 
	OEIS 
	A062870 Number of permutations of degree n with greatest sum of distances.
*/
int main() {
	f[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		f[i] = (f[i-1]*i)%MOD;
		if (i&1) {
			r[i] = f[(i-1)/2]*f[(i-1)/2]%MOD*i%MOD;
		} else {
			r[i] = f[i/2]*f[i/2]%MOD;
		}
	}
	
	int n;
	while (scanf("%d", &n) == 1) {
		printf("%lld\n", r[n]);
	}
	return 0;
}

/*
	OBSERVE:
		When n is even, the solution must be
			the permutation of (n, n-1, ..., n/2)
				concatenates
			the permutation of (n/2-1, n/2-2, ..., 1)
		, so the #solution = [(n/2)!]^2
		
		When n is odd, the solution must be
			1) pick the any number x as the middle number
			2) the first n/2 big numbers in the remaining list
				the permutation as A
			3) the last n/2 small numbers in the remaining list
				the permutation as B
			4) the solution is as A, x, B
		, so the #solution = n * [((n-1)/2)!]^2
*/
/*
#include <bits/stdc++.h>
using namespace std;

int main() {
	int n = 7;
	int t[100] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	int ret = 0;
	do {
		int sum = 0;
		for (int i = 0; i < n; i++)
			sum += abs(t[i]-(i+1));
		if (sum == n*n/2) {
			for (int i = 0; i < n; i++)
				printf("%d ", t[i]);
			printf(": %d\n", sum);
			ret++;
		}
	} while (next_permutation(t, t+n));
	printf("target %d %d\n", n*n/2, ret);
	return 0;
}

*/
