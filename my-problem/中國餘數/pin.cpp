#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
using namespace std;
#define maxL (10000000>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[maxL];
int P[50000], Pt = 0;
void sieve() {
    register int i, j, k;
    SET(1);
    int n = 31622;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
            P[Pt++] = i;
        }
    }
}
long long mul(long long a, long long b, long long mod) { 
	long long ret = 0; 
	for( ; b != 0; b>>=1, (a<<=1)%=mod) 
		if(b&1) (ret += a) %= mod; 
	return ret; 
}
int isPrime(long long x) {
	for (int i = 0; i < Pt && P[i] * P[i] <= x; i++) {
		if (x%P[i] == 0)
			return 0;
	}
	return 1;
}
vector<int> LPrime;
void findPrime() {
	LPrime.clear();
	for (int i = 0; i < 1000; i++) {
		int st = 1e+9 - rand()*rand()%((int)5e+8) - 514;
		for (int j = st, k = 0; k < 514; j++, k++)
			if (isPrime(j))
				LPrime.push_back(j);
	}
	sort(LPrime.begin(), LPrime.end());
	LPrime.resize(unique(LPrime.begin(), LPrime.end()) - LPrime.begin());
	fprintf(stderr, "LP %d\n", LPrime.size());
}
int main() {
	sieve();
	findPrime();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 10000;
	while (testcase--) {
		int x, y;
		do {
			x = rand()%Pt, y = rand()%Pt;
		} while (x == y);
		int p = P[x], q = P[y];
		printf("%d %d %d %d\n", rand(), rand()%((p-1)*(q-1)), p, q);
	}
	testcase = 50000;
	while (testcase--) {
		int x, y;
		do {
			x = rand()%LPrime.size(), y = rand()%LPrime.size();
		} while (x == y);
		long long p = LPrime[x], q = LPrime[y];
		printf("%lld %lld %lld %lld\n", mul(rand()*rand(), rand()*rand(), p*q), 
			mul(rand()*rand(), rand()*rand(), (p-1)*(q-1)), p, q);
	}
	return 0;
}
