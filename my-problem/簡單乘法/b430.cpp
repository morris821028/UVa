#include <bits/stdc++.h> 
using namespace std;

long long mul(long long a, long long b, long long mod) { 
	long long ret = 0; 
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
	long long a, b, n;
	while (scanf("%lld %lld %lld", &a, &b, &n) == 3) 
		printf("%lld\n", mul(a, b, n));
	return 0;
}
/*
61160789839669776 61160789839669776 8223372036854775841
63-bits for unsigned long long 64-bits
*/ 
