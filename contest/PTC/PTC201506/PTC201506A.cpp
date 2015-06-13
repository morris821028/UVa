#include <bits/stdc++.h> 
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
			scanf("%lld", &A[i]);
			
		unordered_map<long long, int> RA, RB;
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

		for (auto&x : RB)
			sum += x.second;
		for (auto&x : RA) {
			long long inv_x = inv(x.first, MOD);
			long long t = (K * inv_x)%MOD;
			if (K == 0 && x.first == 0)
				ret += sum * x.second;
			else if (RB.count(t))
				ret += RB[t] * x.second;
		}
		
		ret += RB[K] + RA[K];
		
		printf("%lld\n", ret);
	}
	return 0;
}
/*
3
3 4
2 2 2
8 24
1 2 3 4 5 6 7 8
2 3
10 100000001

999
5 0
1 0 0 0 0 
5 0
0 0 0 0 1
5 0
0 0 0 0 0
*/
