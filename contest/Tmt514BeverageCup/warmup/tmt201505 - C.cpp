#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <queue>
using namespace std;
#define MAXL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
int P[5500000], Pt = 0;
vector<long long> ret;
void sieve() {
	register int i, j, k;
	SET(1);
	int n = 10000000;
	for(i = 2; i <= n; i++) {
		if(!GET(i)) {
			for (k = n/i, j = i*k; k >= i; k--, j -= i)
				SET(j);
			P[Pt++] = i;
		}
	}
}
long long MAXVAL = 1e+15;
int isprime(long long v) {
	if (v < 2)	
		return 0;
	if (v < 10000000)
		return !GET(v);
	for (int i = 0; i < Pt && (long long) P[i] * P[i] <= v; i++)
		if (v%P[i] == 0)
			return 0;
	return 1;
}
void make() {
	for (int i = 0; i < Pt && P[i] < 100000; i++) {
		for (int j = P[i] + P[i]-1; j < 1000000; j += P[i] - 1) {
			if (!isprime(j))
				continue;
			long long A = (j - P[i])/(P[i]-1);
			long long B = P[i] - A;
			long long m = P[i], cnt = 1, mm = P[i];
			while (mm <= MAXVAL) {
				if (A && MAXVAL / m / A <= 0)
					break;
				if (m * A + B <= m)
					break;
				m = m * A + B;
				if (MAXVAL / mm / m <= 0)
					break;
				if (!isprime(m))
					break;
//				printf("%lld ", m);
				mm = mm * m, cnt ++;
				if (cnt >= 3) {
					ret.push_back(mm);
//					printf("%lld %lld %lld\n", mm, A, B);
				}
			}
		}
	}
	sort(ret.begin(), ret.end());
	for (int i = 0; i < 243; i++)
		printf("%d\n", ret[i]);
//	printf("%d\n", ret.size());
}
int main() {
	sieve();
	make();
	int testcase;
	long long L, R;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld", &L, &R);
		int r = 0;
		for (int i = 0; i < ret.size(); i++)
			r += ret[i] >= L && ret[i] <= R;
		printf("%d\n", r);
	}
	return 0;
}
/*

2
4505 4505
0 5000
*/
