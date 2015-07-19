#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
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
unsigned long long mpow(unsigned long long x, unsigned long long y, unsigned long long mod) {
	unsigned long long ret = 1;
	while (y) {
		if (y&1) 
			ret = (ret * x)%mod;
		y >>= 1, x = (x * x)%mod;
	}
	return ret % mod;
}
int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	freopen("in.txt", "w+t", stdout);
	testcase = 5; 
	const long long M = 1LL<<20;
	const long long E = 23333;
	ofstream fout("out222.txt");
	map<long long, int> R;
	for (int i = 0; i < M; i++)
		R[mpow(i, E, M)]++;
	int cnt = 0;
	for (auto &x : R)
		cnt += x.second == 1;
	fprintf(stderr, "test %d\n", cnt);
	
	testcase = 65536;
	while (testcase--) {
		int res = ((rand()*rand()%M + 1) | 1)%M;
		long long t = mpow(res, E, M);
		printf("%llu\n", t);
//		fprintf(stderr, "%d\n", res);
		fout << res << endl; 
	}
	
//	testcase = 5;
//	while (testcase--) {
//		int res = (rand()%1000 %M + 1) | 1;
//		long long t = mpow(res, E, M);
//		do {
//			int cnt = 0;
//			for (long long i = 0; i < M && cnt < 2; i++)
//				if (mpow(i, E, M) == t)
//					cnt++;
//			if (cnt == 1)
//				break;
//			res = (rand()%1000 %M + 1) | 1;
//			t = mpow(res, E, M);
//		} while (true);
//		printf("%llu\n", t);
//		fprintf(stderr, "%d\n", res);
//		fout << res << endl; 
//	}
	fout.close();
	return 0;
}
