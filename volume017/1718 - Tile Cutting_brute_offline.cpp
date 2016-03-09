#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <algorithm>
#include <complex>
using namespace std;

long long ret[1048576];
long long pr[1048576] = {};
int main() {
	int m;
	const int N = 500000;
	for (m = 1; m < (N<<1); m <<= 1);
	/*
		(a + c)(b + d) - 2 * 0.5 * (a b) - 2 * 0.5 * (c * d)
		= ad + bc = area
		a, b, c, d > 0,
		ways of area = #(a, b, c, d) sat. ad + bc = area
	*/
    for (int i = 1; i <= N; i++) {
    	for (int j = i; j <= N; j += i)
    		pr[j]++;
	}
	
	for (int i = 1; i <= N; i++) {
		long long ret = 0;
		for (int j = 1; j <= i; j++) {
			ret += pr[j] * pr[i-j];
		}
		printf("%lld\n", ret);
	}
	
    return 0;
}
