#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <assert.h>
using namespace std;
void inv(char s[], int n) {
	for (int i = 0, j = n-1; i < j; i++, j--)
		swap(s[i], s[j]);
}
int dp[64][64][2][2];
int main() {
	int testcase;
	char s1[64], s2[64];
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		gets(s1);
		gets(s2);
		int n1 = strlen(s1), n2 = strlen(s2);
		inv(s1, n1), inv(s2, n2);
		for (int i = 0; i <= n1; i++) {
			for (int j = 0; j <= n2; j++) {
				dp[i][j][0][0] = dp[i][j][0][1] = -0x3f3f3f3f;
				dp[i][j][1][0] = dp[i][j][1][1] = -0x3f3f3f3f;
			}
		}
		dp[0][0][0][1] = 0;
		dp[0][0][1][1] = 0;
		int ret = -0x3f3f3f3f;
		for (int i = 0; i <= n1; i++) {
			for (int j = 0; j <= n2; j++) {
				int v = max(dp[i][j][0][0], dp[i][j][0][1]);
				v = max(v, max(dp[i][j][1][0], dp[i][j][1][1]));
				dp[i+1][j+1][0][1] = max(dp[i+1][j+1][0][1], v);
				dp[i+1][j+1][1][1] = max(dp[i+1][j+1][1][1], v);
				if (s1[i] == s2[j]) {
					dp[i+1][j+1][0][1] = max(dp[i+1][j+1][0][1], v + 2);
					dp[i+1][j+1][1][1] = max(dp[i+1][j+1][1][1], v + 2);
				}
				dp[i+1][j][0][0] = max(dp[i+1][j][0][0], dp[i][j][0][0]);
				dp[i+1][j][0][0] = max(dp[i+1][j][0][0], dp[i][j][1][0] - 1);
				dp[i+1][j][0][0] = max(dp[i+1][j][0][0], dp[i][j][0][1] - 1);
				dp[i+1][j][0][0] = max(dp[i+1][j][0][0], dp[i][j][1][1] - 1);
				
				dp[i][j+1][1][0] = max(dp[i][j+1][1][0], dp[i][j][1][0]);
				dp[i][j+1][1][0] = max(dp[i][j+1][1][0], dp[i][j][0][0] - 1);
				dp[i][j+1][1][0] = max(dp[i][j+1][1][0], dp[i][j][0][1] - 1);
				dp[i][j+1][1][0] = max(dp[i][j+1][1][0], dp[i][j][1][1] - 1);
				if (j == n2 || i == n1) {
					ret = max(ret, max(dp[i][j][0][0], dp[i][j][0][1]));
					ret = max(ret, max(dp[i][j][1][0], dp[i][j][1][1]));
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
2
AADDEFGGHC
ADCDEGH
ERTTHCBYNQC
BEARTBCHQYN

3
ABC
ABC
ABC
AC
BAC
AC

*/
