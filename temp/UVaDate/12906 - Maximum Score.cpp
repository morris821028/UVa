#include <stdio.h> 
#include <vector> 
#include <string.h>
#include <algorithm>
using namespace std;
// greedy, math
// make one peak sequence
const long long MOD = 1000000007;

int main() {
	int testcase, cases = 0;
	int n;
	long long v, f;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		vector< pair<long long, long long> > A;
		long long N = 0;
		for (int i = 0; i < n; i++) {
			scanf("%lld %lld", &v, &f);
			A.push_back(make_pair(v, f)), N += f;
		}
		
		sort(A.begin(), A.end());
		unsigned long long mx_score = 0;  // tricky unsigned long long !!!
		long long mx_ways = 1;
				
		mx_score += N * A[n-1].second;
		N -= A[n-1].second;
		for (int i = n-2; i >= 0; i--) {
			mx_score += A[i].second * N; 
			mx_ways = mx_ways * (A[i].second + 1) %MOD;
			N -= A[i].second;
		}
		printf("Case %d: %llu %lld\n", ++cases, mx_score, mx_ways);
	}
	return 0;
}
/*
9999
1
50 50
*/
