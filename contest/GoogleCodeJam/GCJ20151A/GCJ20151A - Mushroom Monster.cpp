// Fucking English
#include <stdio.h> 
#include <algorithm>
using namespace std;

int main() {
	int testcase, n, cases = 0;
	long long A[1024];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		for (int i = 0; i < n; i++)
			scanf("%lld", &A[i]);
		
		long long retA = 0, retB = 0, mx = 0;
		for (int i = 1; i < n; i++) {
			if (A[i-1] - A[i] > 0) {
				retA += A[i-1] - A[i];
				mx = max(mx, A[i-1] - A[i]);
			}
		}
		for (int i = 0; i < n - 1; i++) {
			if (A[i] > mx)
				retB += mx;
			else
				retB += A[i];
		}
		
		printf("Case #%d: %lld %lld\n", ++cases, retA, retB);
	}
	return 0;
}
/*
4
4
10 5 15 5
2
100 100
8
81 81 81 81 81 81 81 0
6
23 90 40 0 100 9
*/
