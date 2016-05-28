#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <omp.h>
using namespace std;
const int MAXN = 65536;
static char A[MAXN], B[MAXN];
int lcs_len(const char *A, int na, const char *B, int nb, int dp[][MAXN]) {
	if (na > nb)
		swap(A, B), swap(na, nb);
	memset(dp[0], 0, sizeof(int)*(nb+1));
	dp[1][0] = 0;
	for (int i = 1; i <= na; i++) {
		for (int j = 1; j <= nb; j++) {
			if (A[i-1] == B[j-1])
				dp[1][j] = dp[0][j-1]+1;
			else
				dp[1][j] = max(dp[1][j-1], dp[0][j]);
		}
		memcpy(dp[0], dp[1], sizeof(int)*(nb+1));
	}
	return dp[0][nb];
}
int main() {
	int dp[2][MAXN];
	while (scanf("%s %s", A, B) == 2) {
		int len = lcs_len(A, strlen(A), B, strlen(B), dp);
		printf("%d\n", len);
	}
	return 0;
}


