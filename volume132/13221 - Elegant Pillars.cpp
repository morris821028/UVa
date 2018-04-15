#include <bits/stdc++.h> 
using namespace std;
/*
similar: UVa 10276 - Hanoi Tower Troubles Again
formula: https://oeis.org/A047838
*/
int main() {
	int64_t n;
	while (scanf("%lld", &n) == 1) {
		int64_t ret = (n+1)*(n+1)/2 - 1;
		printf("%lld\n", ret);
	}
	return 0;
}
