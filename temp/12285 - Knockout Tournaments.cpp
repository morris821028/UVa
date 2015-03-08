// Euler¡VMascheroni constant, harmonic series
#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;
#define MAXN 20000000
long double sum[MAXN];
long double H(long long x) {
	if (x < MAXN)  return sum[x];
	return 0.57721566490153286l + logl((long double)x);
}

int main() {
	for (int i = 1; i < MAXN; i++)
		sum[i] = sum[i-1] + 1.0l / (long double) i;
	long long W, L;
	int cases = 0;
	while (scanf("%lld %lld", &W, &L) == 2) {
		if (W == 0 && L == 0) 
			return 0;
		printf("Case %d:\n", ++cases);
		long double ret = 0;
		if (L == 0 && W%8) {
			ret = -1;
		} else if (L == 0 && W%8 == 0) {
			ret = 8;
		} else {
			long long round = ceil((W - L * 7) / 8.0), n = W / 8;
			if (round < 0)	round = 0;
			ret = (H(n + L) - H(L + round - 1));
			ret *= (W + L);
			ret /= (n - round + 1);
			assert(ret > -0.1);
		}
		if (ret > -0.1)
			printf("On Average Bob Reaches Round %.2lf\n", (double) ret);
		else 
			printf("Situation Impossible.\n");
	} 
	return 0;
}
/*
200000000 200000000

1 0
8 0
16 0
30 2
50 4
4 0

24 16
89 59
71 7
68 38
45 17
87 70
19 41
82 70
98 61
50 4

*/
