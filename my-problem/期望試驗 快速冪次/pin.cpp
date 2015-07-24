#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <set>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;
typedef unsigned long long UINT64;
UINT64 mul(UINT64 a, UINT64 b, UINT64 mod) { 
	UINT64 ret = 0; 
	for (a %= mod, b %= mod; b != 0; b>>=1, a <<= 1, a = a >= mod ? a - mod : a) { 
		if (b&1) {
			ret += a;
			if (ret >= mod) 
				ret -= mod;
		} 
	} 
	return ret; 
}
int main() {
//	sieve();
	srand (time(NULL));
	int testcase, n, m, x, y, a, b;
	unsigned long long LIMIT = 1e+18;
	freopen("in.txt", "w+t", stdout);
	testcase = 1000; 
	fprintf(stderr, "LIMIT = %llu\n", LIMIT);
	while (testcase--) {
		printf("%llu ", mul(rand() * rand(), rand() * rand(), LIMIT) + 1);
		int n = 1<<2;
		for (int i = 0; i < n; i++)
			printf("%d", rand()%2);
		printf(" %llu\n", LIMIT - mul(rand() * rand(), rand() * rand(), 10000000) + 1);
	}	
	return 0;
}
