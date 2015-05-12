#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>
using namespace std;

int dp[512][512]; // dp[i-th match in A][#miss match in B]
void solve(vector<int> A, vector<int> B) {
	assert(A.size() <= B.size());
	int n1 = A.size(), n2 = B.size();
	int diff = n2 - n1;
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());
	
	for (int i = 0; i < n1; i++) {
		int mn = 0x3f3f3f3f;
		for (int j = 0; j <= diff; j++) {
			if (i == 0)
				mn = 0;
			else
				mn = min(mn, dp[i-1][j]);
			dp[i][j] = mn + abs(A[i] - B[i + j]);
		}
	}
	
	int ret = 0x3f3f3f3f;
	for (int i = 0; i <= diff; i++)
		ret = min(ret, dp[n1-1][i]);
	printf("%d.%d\n", ret/10, ret%10);
}
int main() {
	int testcase;
	int n1, n2, x, y;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n1, &n2);
		vector<int> A, B;
		for (int i = 0; i < n1; i++) {
			scanf("%d.%d", &x, &y);
			A.push_back(x * 10 + y);
		} 
		for (int i = 0; i < n2; i++) {
			scanf("%d.%d", &x, &y);
			B.push_back(x * 10 + y);
		} 
		
		if (n1 < n2)
			solve(A, B);
		else
			solve(B, A);
	}
	return 0;
}
