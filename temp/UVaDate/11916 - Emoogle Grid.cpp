#include <stdio.h> 
#include <math.h>
#include <unordered_map>
#include <set>
using namespace std;

// Baby-step Giant-step Algorithm
// a x + by = g
void exgcd(long long  x, long long y, long long &g, long long &a, long long &b) {
	if (y == 0)
		g = x, a = 1, b = 0;
	else
		exgcd(y, x%y, g, b, a), b -= (x/y) * a;
}
long long inverse(long long x, long long p) {
	long long g, b, r;
	exgcd(x, p, g, r, b);
	if (g < 0)	r = -r;
	return (r%p + p)%p;
}
long long BSGS(long long P, long long B, long long N) { // find B^L = N mod P
	unordered_map<long long, int> R;
	long long sq = (long long) sqrt(P);
	long long t = 1, f;
	for (int i = 0; i < sq; i++) {		
		if (t == N)	
			return i; 		
		if (!R.count(t))
			R[t] = i;
		t = (t * B) % P;
	}
	
	f = inverse(t, P);
	for (int i = 0; i <= sq+1; i++) {
		if (R.count(N))
			return i * sq + R[N];
		N = (N * f) % P;
	}
	return -1;
}
long long mpow(long long x, long long y, long long mod) {
	long long ret = 1;
	while (y) {
		if (y&1)
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret;
}

const long long MOD = 100000007;
long long solve(long long N, long long K, long long B, long long R, long long M, set< pair<int, int> > &g) {
	int usedK; // first row
	long long way;
	
	usedK = N;
	for (auto&x : g) {
		if (x.first != M && !g.count(make_pair(x.first+1, x.second)))
			usedK++;
		if (x.first == 1)
			usedK--;
	}
	
	way = (mpow(K, usedK, MOD) * mpow(K-1, N*M - B - usedK, MOD))%MOD;
	if (way == R)
		return M;
		
	usedK = N;
	for (auto&x : g) {
		if (!g.count(make_pair(x.first+1, x.second)))
			usedK++;
		if (x.first == 1)
			usedK--;
	}
	M += 1;
	way = (mpow(K, usedK, MOD) * mpow(K-1, N*M - B - usedK, MOD))%MOD;
	return BSGS(MOD, mpow(K-1, N, MOD), (inverse(way, MOD)*R)%MOD) + M;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long N, K, B, R, X, Y;
		long long M = 1;
		set< pair<int, int> > g;
		scanf("%lld %lld %lld %lld", &N, &K, &B, &R);
		for (int i = 0; i < B; i++) {
			scanf("%lld %lld", &X, &Y);
			M = max(M, X);
			g.insert(make_pair(X, Y));
		}
		
		printf("Case %d: %lld\n", ++cases, solve(N, K, B, R, M, g));
	}
	return 0;
}
/*
5 2 3
*/
