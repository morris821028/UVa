#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;
void exgcd(long long x, long long y, long long &g, 
	long long &a, long long &b) {
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

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int N, M, R[2048], S = 0, mxR = 0;
		scanf("%d %d", &N, &M);
		for (int i = 0; i < N; i++)
			scanf("%d", &R[i]), S += R[i], mxR = max(mxR, R[i]);
		if (N == 1) {
			printf("Case #%d: %lld\n", ++cases, M);
			continue;
		}
		fprintf(stderr, "%d %d %d\n", N, S, M);
		long long invNplus = 1;
		map<long long, long long> C;
		{
			long long f = 1;
			for (int i = 1; i <= N; i++)
				f = (f * i)%MOD;
			invNplus = inverse(f, MOD);
			
			int l = 1, r = 1;
			f = 1;
			for (int i = M - 2*S; i <= M - 2*S + 2*mxR; i++) {
				int tM = i+N-1;
				if (tM < N)
					continue;
				int L = tM-N+1, R = tM;
				if (r < L)
					l = r = f = L;
				while (l < L)
					f = (f*inverse(l, MOD))%MOD, l++;
				while (r < R)
					r++, f = (f * r)%MOD;
				C[tM] = (f * invNplus)%MOD;
//				printf("C(%lld %d) = %lld, %lld\n", tM, N, C[tM], f);
			}
		}
		long long ret = 0;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (i == j)
					continue;
				int tM = M + R[i] + R[j] - 2*S;
				if (tM+N-1 < N)
					continue;
//				printf("add C(%d %d)\n", tM+N-1, N);
				ret += C[tM+N-1];
				ret %= MOD;
			}
		}
		
		long long f = 1;
		for (int i = 1; i <= N-2; i++)
			f = (f * i)%MOD;
		ret = ret * f;
		ret %= MOD;
		assert(ret >= 0);
		printf("Case #%d: %lld\n", ++cases, ret);
	}
	return 0;
}
