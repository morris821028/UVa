#include <bits/stdc++.h>
using namespace std;
/*
	for (int i = 1; i <= n; i++)
		ret += i * (n/i);
*/
long long MSLCM(long long n) {
	long long l = 1, r, val;
	long long ret = 0;
	while (l <= n) {
		val = n / l;
		r = n / val;
		ret += val * ((l+r)*(r-l+1)/2);
		l = r+1;
	}
	return ret-1;
}
int main() {
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("%lld\n", MSLCM(n));
	}
	return 0;
}

