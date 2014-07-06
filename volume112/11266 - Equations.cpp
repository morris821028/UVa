#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int shift = 100000;
int dp[2][200005];
int main() {
	int testcase, n, s;
	int A[16], B[16];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%d %d", &n, &s);
		for(int i = 0; i < n; i++)
			scanf("%d %d", &A[i], &B[i]);
			
		memset(dp, 0, sizeof(dp));
		for(int i = A[0]; i <= B[0]; i++)
			dp[0][i + shift] = 1;
		int f = 1;
		for(int i = 1; i < n; i++) {
			memset(dp[f], 0, sizeof(dp[f]));
			int l = -B[i], r = -A[i], sum = 0;
			for(int j = 0 - B[i]; j <= 0 - A[i]; j++) {
				if(j < 0 || j >= 200005)
					continue;
				sum += dp[!f][j];
				sum %= 200003;
			}
			for(int j = 0; j < 200005; j++) {
				dp[f][j] = sum;
				if(l >= 0 && l < 200005)
					sum -= dp[!f][l];
				if(r + 1 >= 0 && r + 1 < 200005)
					sum += dp[!f][r+1];
//				if(sum)
//					printf("%d %d %d\n", i, j - shift, sum);
				sum %= 200003;
				l++, r++;
			}
			f = !f;
		}
		printf("%d\n", (dp[!f][s + shift] + 200003)%200003);
	}
	return 0;
}
