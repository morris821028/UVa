#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 105;
int A[MAXN][MAXN], B[MAXN][MAXN];
int solve(int n, int m) {
	int diff = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			diff += A[i][j] != B[i][j];
	}
	if (diff == 0)
		return 0;
	int diff_sym = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++)
			diff_sym += B[i][j] != B[j][i];
	}
	if (diff_sym == 0)
		return -1;
	// special case: transpose A^T = B
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			// A^T != B
			if (A[i][j] != B[j][i] || A[j][i] != B[i][j])
				return diff;
			if (B[i][j] != B[j][i]) {
				if (A[i][j] != B[i][j] || A[j][i] != B[j][i])
					cnt++;
			}
		}
	}
	if (cnt > 1)
		return diff;
	if (n == 2 && m == 2)
		return -1;
	if (m == 2)
		return diff+2;
	else
		return diff+1;
}
int main() {
	int testcase, cases = 0;
	int n, m;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				scanf("%d", &A[i][j]);
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				scanf("%d", &B[i][j]);
		}
		int ret = solve(n, m);
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
