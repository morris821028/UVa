#include <stdio.h> 
#include <map>
#include <algorithm>
using namespace std;

const unsigned long long MOD = 1000007;
unsigned long hash(unsigned long long x) {
	return (x * x)% MOD;
}
map<long long, int> dp[MOD];
int n;
long long m, A[64], sum[1<<20];
void meetInMiddle() {
	sort(A, A+n);
	// D&C, dp, bitmask
	long long ret = 0;
	int div1 = n/2, div2 = n - n/2;
	
	for (int i = 0; i < MOD; i++)
		dp[i].clear();
	
	for (int i = 0; i < div1; i++)
		sum[1<<i] = A[i];
	for (int i = 0; i < (1<<div1); i++) {
		sum[i] = sum[i - ((i-1)&i)] + sum[(i-1)&i];
		long long x = sum[i];
		dp[hash(x)][x]++;
	}
	for (int i = 0; i < div2; i++)
		sum[1<<i] = A[i + div1];
	for (int i = 0; i < (1<<div2); i++) {
		sum[i] = sum[i - ((i-1)&i)] + sum[(i-1)&i];
		long long x = sum[i];
		if (dp[hash(m - x)].count(m - x))
			ret += dp[hash(m - x)][m - x];
	}
	if (m == 0)		ret--;
	printf("%lld\n", ret);
}
int main() {
	while (scanf("%d %lld", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%lld", &A[i]);
		
		meetInMiddle();
	}
	return 0;
}
/*
6 0
-1 2 -3 4 -5 6
5 0
-7 -3 -2 5 8
40 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
5 2
1 1 1 1 1
6 1
1 2 3 -2 -1 -3
6 -1
0 0 0 0 0 0
*/
