#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;
long long C[25][25] = {};
long long M[25] = {}, A[25][25] = {};
long long llabs(long long v) {
	return v < 0 ? -v : v;
}
void init() {
	C[0][0] = 1;
	for(int i = 1; i < 25; i++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j++)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	// sum of powers
	M[0] = 1, A[0][1] = 1; // sigma(k^0) = n
	for(int i = 1; i <= 20; i++)  {
		M[i] = i + 1;
		long long val = 1;
		for(int j = 0; j <= i - 1; j++)
			val = val / __gcd(val, M[j]) * M[j];
		M[i] *= val;
//		printf("%lld %lld\n", M[i], val);
		for(int j = 0; j <= i - 1; j++)
			for(int k = 0; k <= j + 1; k++)
				A[i][k] -= A[j][k] * val / M[j] * C[i + 1][j];
		for(int j = 0; j <= i + 1; j++)
			A[i][j] += val * C[i+1][j];
		A[i][0] -= val * 1;
		long long g = M[i];
		for(int j = 0; j <= i + 1; j++)
			g = __gcd(g, llabs(A[i][j]));
		M[i] /= g;
		for(int j = 0; j <= i + 1; j++)
			A[i][j] /= g;
	}
}
/*
find sigma(i^2)
(i + 1)^3 - (i)^2 = 3*(i)^2 + 3i + 1
=> i^2 = 1/3 * ((i + 1)^3 - (i)^2 - 3i - 1)
=> sigma(i^2) = sigma(1/3 * ((i + 1)^3 - (i)^2 - 3i - 1))
=>            = 1/3 (sigma((i + 1)^3 - (i)^2) + sigma(-3i - 1)) 
=> // sigma((i + 1)^3 - (i)^3) = (n + 1)^3 - 1
=>            = 1/3 ((n + 1)^3 - 1 + sigma(-3i - 1)) 
... so
 */
int main() {
	init();
	int testcase, n;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d", &n);
		printf("%lld", M[n]);
		for(int i = n + 1; i >= 0; i--)
			printf(" %lld", A[n][i]);
		puts("");
		if(testcase)
			puts("");
	}
	return 0;
}
