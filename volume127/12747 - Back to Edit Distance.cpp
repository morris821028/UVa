#include <stdio.h> 
#include <vector>
#include <algorithm>
using namespace std;
// LCS to LIS
int A[262144], B[262144];
int LIS(int A[], int n) {
	vector<int> r;
	r.push_back(A[0]);
	for (int i = 1; i < n; i++) {
		int pos = (int)(upper_bound(r.begin(), r.end(), A[i]) - r.begin());
		if (pos == r.size())
			r.push_back(A[i]);
		else
			r[pos] = A[i];
	}
	return r.size();
}
int main() {
	int testcase, cases = 0;
	int n, x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			A[x] = i;
		}
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			B[i] = A[x];
		}
		printf("Case %d: %d\n", ++cases, (n - LIS(B, n)) * 2);
	}
	return 0;
}
/*
2
5
1 3 5 4 2
1 5 4 3 2
4
1 2 4 3
3 4 2 1
*/
