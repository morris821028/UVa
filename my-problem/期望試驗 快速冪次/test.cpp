#include <bits/stdc++.h> 
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
UINT64 mpowR2L(UINT64 x, char y[], UINT64 z) {
	int n = (int) strlen(y);
	UINT64 ret = 1;
	for (int i = n-1; i >= 0; i--) {
		if (y[i] == '1')
			ret = mul(ret, x, z);
		x = mul(x, x, z);
	}
	return ret;
}
UINT64 mpowL2R2(UINT64 x, char y[], UINT64 z) {
	int n = (int) strlen(y);
	UINT64 x2 = mul(x, x, z);
	UINT64 x3 = mul(x2, x, z);
	UINT64 ret = 1;
	for (int i = n&1; i < n; i += 2) {
		ret = mul(ret, ret, z);
		ret = mul(ret, ret, z);
		if (y[i] == '1') {
			if (y[i+1] == '1')
				ret = mul(ret, x3, z);
			else if (y[i+1] == '0')
				ret = mul(ret, x2, z); 
		} else if (y[i+1] == '1') {
			ret = mul(ret, x, z);
		}
	}
	return ret;
}
UINT64 mpowL2RS(UINT64 x, char y[], UINT64 z) {
	int n = (int) strlen(y);
	UINT64 x3 = mul(mul(x, x, z), x, z);
	UINT64 ret = 1;
	for (int i = n&1; i < n; ) {
		ret = mul(ret, ret, z);
		if (y[i] == '1' && y[i+1] == '1') {
			ret = mul(ret, ret, z);
			ret = mul(ret, x3, z);
			i += 2;
		} else if (y[i] == '0' && y[i+1] == '0') {
			ret = mul(ret, ret, z);
			i += 2; 
		} else if (y[i] == '1') {
			ret = mul(ret, x, z);
			i ++;
		} else {
			i++;
		}
	}
	return ret;
}
int main() {
	char y[65536] = "0";
	long long x, z;
	while (scanf("%lld %s %lld", &x, y+1, &z) == 3) {
//		printf("%llu - %llu - %llu\n", mpowR2L(x, y, z), mpowL2R2(x, y, z), mpowL2RS(x, y, z));
	}
	return 0;
}
/*
5 1 7
5 10 7
5 101 7
3 110 7
*/
