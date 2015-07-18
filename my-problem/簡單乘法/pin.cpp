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
    int n = 30000;
    for(i = 2; i <= n; i++) {
        if(!GET(i)) {
            for(k = n/i, j = i*k; k >= i; k--, j -= i)
                SET(j);
        	if (i%4 == 3)
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
int main() {
	sieve();
	 srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 10000;
	while (testcase--) {
		printf("%d %d %d\n", rand()%100, rand()%100, rand()%100+1);
	}
	testcase = 10000;
	while (testcase--) {
		int n = rand() + 10000;
		printf("%d %d %d\n", rand()%10000, rand()%10000, n);
	}
	testcase = 10000;
	while (testcase--) {
		long long n = rand() + 10000000;
		printf("%d %d %lld\n", rand() * rand()%10000, rand()*rand()%10000, n);
	}
	testcase = 50000;
	while (testcase--) {
		long long n = mul(rand() * rand(), rand() * rand(), 1e+17) + 1e+17;
		printf("%lld %lld %lld\n", mul(rand() * rand(), rand() * rand(), n), 
			mul(rand() * rand(), rand() * rand(), n), n);
	}
	testcase = 50000;
	while (testcase--) {
		long long n = 1e+18 - 514;
		printf("%lld %lld %lld\n", mul(rand() * rand(), rand() * rand(), n), 
			mul(rand() * rand(), rand() * rand(), n), n);
	}
	return 0;
}
