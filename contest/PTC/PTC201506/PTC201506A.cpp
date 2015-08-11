#include <stdio.h> 
#include <map>
#include <algorithm> 
using namespace std;

void exgcd(long long x, long long y, long long &g, long long &a, long long &b) {
	if (y == 0)
		g = x, a = 1, b = 0;
	else
		exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long inv(long long x, long long p) {
	long long g, a, b;
	exgcd(x, p, g, a, b);
	if (g < 0)	a = -a;
	return (a%p + p)%p;
}
 
const long long MOD = 1000000007;
int main() {
	int testcase;
	long long N, K, A[32];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld", &N, &K);
		for (int i = 0; i < N; i++)
			scanf("%lld", &A[i]), A[i] %= MOD;
		sort(A, A+N);
		if (K == 0) {
			int zero = 0, noz = 0;
			for (int i = 0; i < N; i++)
				zero += A[i] == 0;
			noz = N - zero;
			long long ret = 0;
			ret += (1LL<<zero)-1; // itself
			ret += ((1LL<<zero)-1)*((1LL<<noz)-1);
			printf("%lld\n", ret);
			continue;
		}
		map<long long, int> RA, RB;
		int div1 = N/2;
		int div2 = N - N/2;
		
		for (int i = (1<<div1)-1; i >= 1; i--) {
			long long s = 1;
			for (int j = 0; j < div1; j++) {
				if ((i>>j)&1)
					s = (s * A[j])%MOD; 
			}
			RA[s]++;
		}
		for (int i = (1<<div2)-1; i >= 1; i--) {
			long long s = 1;
			for (int j = 0; j < div2; j++) {
				if ((i>>j)&1)
					s = (s * A[j + div1])%MOD; 
			}
			RB[s]++;
		}
		
		long long ret = 0, sum = 0;

		for (map<long long, int>::iterator it = RB.begin();
			it != RB.end(); it++) {
			pair<long long, int> x = *it;
			sum += x.second;
		}
		for (map<long long, int>::iterator it = RA.begin();
			it != RA.end(); it++) {
			pair<long long, int> x = *it;
			if (x.first == 0)
				continue;
			long long inv_x = inv(x.first, MOD);
			long long t = (K * inv_x)%MOD;
			ret += (long long) RB[t] * x.second;
		}
		
		ret += RB[K] + RA[K];
		
		printf("%lld\n", ret);
	}
	return 0;
}

