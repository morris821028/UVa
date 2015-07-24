#include <bits/stdc++.h> 
using namespace std;

typedef unsigned long long UINT64;
UINT64 mul(UINT64 a, UINT64 b, UINT64 mod) { 
	UINT64 ret = 0; 
	for (a = a >= mod ? a%mod : a, b = b >= mod ? b%mod : b; b != 0; b>>=1, a <<= 1, a = a >= mod ? a - mod : a) { 
		if (b&1) {
			ret += a;
			if (ret >= mod) 
				ret -= mod;
		} 
	} 
	return ret; 
}

UINT64 mpowL2RS(UINT64 x, char y[], UINT64 z) {
	UINT64 x3 = mul(mul(x, x, z), x, z);
	UINT64 ret = 1;
	for (int i = 0; y[i]; ) {
		ret = mul(ret, ret, z);
		if (y[i] == '1' && y[i+1] == '1') {
			ret = mul(ret, ret, z);
			ret = mul(ret, x3, z);
			i += 2;
		} else if (y[i] == '1') {
			ret = mul(ret, x, z);
			i ++;
		} else if (y[i+1] == '0') {
			ret = mul(ret, ret, z);
			i += 2; 
		} else {
			i++;
		}
	}
	return ret;
}
#define PREPROC 8
UINT64 mpowCHEAT(UINT64 x, char y[], UINT64 z) {
	int n;
	for (n = 1; y[n]; n <<= 1);
	if (n < 1<<PREPROC)
		return mpowL2RS(x, y, z);
	UINT64 X[1<<PREPROC] = {1};
	for (int i = 1; i < (1<<PREPROC); i++)
		X[i] = mul(X[i-1], x, z);
	UINT64 ret = 1;
	for (int i = 0, v; y[i]; i += PREPROC) {
		ret = mul(ret, ret, z);
		ret = mul(ret, ret, z);
		ret = mul(ret, ret, z);
		ret = mul(ret, ret, z);
		ret = mul(ret, ret, z);
		ret = mul(ret, ret, z);
		ret = mul(ret, ret, z);
		ret = mul(ret, ret, z);
		v = (y[i]-'0')<<7|(y[i+1]-'0')<<6|(y[i+2]-'0')<<5|(y[i+3]-'0')<<4|(y[i+4]-'0')<<3|(y[i+5]-'0')<<2|(y[i+6]-'0')<<1|(y[i+7]-'0'); 
		ret = mul(ret, X[v], z);
	}
	return ret;
}
char y[(1<<20) + 5];
int main() {
	long long x, z;
	while (scanf("%lld %s %lld", &x, y, &z) == 3) {
		printf("%llu\n", mpowCHEAT(x, y, z));
	}
	return 0;
}
/*
5 01 7
5 10 7
5 0101 7
3 0110 7
*/
