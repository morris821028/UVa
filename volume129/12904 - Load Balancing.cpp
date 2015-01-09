#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;
#define MAXV 165
#define eps 1e-6
int main() {
	int testcase, n, x;
	int cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		int A[MAXV] = {};
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			A[x]++;
		}
		for (int i = 1; i < MAXV; i++)
			A[i] += A[i-1];
		double dp[5][MAXV];
		int used[5][MAXV] = {};
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < MAXV; j++) {
				dp[i][j] = 1e+30;
			}
		}
		dp[0][0] = 0;
		double avg = n/4.0;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < MAXV; j++) {
				if (dp[i][j] == 1e+30)
					continue;
				for (int k = j; k < MAXV; k++) {
					int cnt = A[k] - (j ? A[j-1] : 0);
					dp[i+1][k+1] = min(dp[i+1][k+1], fabs(cnt - avg) + dp[i][j]);
				}
			}
		}
		used[4][MAXV - 1] = 1;
		for (int i = 3; i >= 0; i--) {
			for (int j = 0; j < MAXV; j++) {
				if (dp[i][j] == 1e+30)
					continue;
				for (int k = j; k < MAXV; k++) {
					int cnt = A[k] - (j ? A[j-1] : 0);
					if (fabs(fabs(cnt - avg) + dp[i][j] - dp[i+1][k+1]) < eps)
						used[i][j] |= used[i+1][k+1];
				}
			}
		}
		
		printf("Case %d:", ++cases);
		
		int pos = 0;
		for (int i = 0; i < 3; i++) {
			for (int k = pos; k < MAXV; k++) {
				int cnt = A[k] - (pos ? A[pos-1] : 0);
				if (fabs(fabs(cnt - avg) + dp[i][pos] - dp[i+1][k+1]) < eps && used[i+1][k+1]) {
					printf(" %d", k);
					pos = k+1;
					break;
				}
			}
		}
		puts("");
	}
	return 0;
}
/*
2

8
0
40
41
80
85
120
150
155

9
0
40
41
80
85
120
121
150
155

Case 1: 40 80 120
Case 2: 40 80 120
*/
