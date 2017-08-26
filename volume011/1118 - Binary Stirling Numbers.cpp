#include <bits/stdc++.h>
using namespace std;

// https://en.wikipedia.org/wiki/Stirling_numbers_of_the_second_kind#Parity
int main() {
	/*
		Stirling numbers S(n,m) = {n, m} = mS(n-1, m)+S(n-1, m-1)
		{n, k} = C(z, w) mod 2
		, z = n - ceil((k+1)/2)
		, w = floor((k-1)/2)
	*/
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);
		int z = n - (m+2)/2;
		int w = (m-1)/2;
		printf("%d\n", (z&w) == w);
	}
	return 0;
}
