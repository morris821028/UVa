// I don't know why, but I got accepted. 
#include <stdio.h> 
#include <string.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
using namespace std;

int main() {
	int testcase, cases = 0;
	char s[1024];
	scanf("%d", &testcase);
	while (getchar() != '\n');
	while (testcase--) {
		scanf("%s", s);
		int n = strlen(s);
		int dp[128][128] = {};
		for (int i = 1; i < n; i++)  {
			for (int j = 0; i + j < n; j++) {
				if (i == 1) 
					dp[j][j+1] = s[j] == s[j+1];
				else {
					if (s[j] == s[i+j]) {
						dp[j][j+i] += dp[j+1][j+i-1];
					}
					for (int k = j+1; k < j+i-1; k++) {
						if (s[j] == s[k]) {
							for (int p = k+1; p <= j+i-1; p++) {
								if (s[p] == s[j+i]) {
									int a;
									if (k+1 == p)	a = 1;
									else			a = dp[k+1][p-1];
									dp[j][j+i] += dp[j][k] * dp[p][j+i] * a;
								}
							}
						}
					}
				}
				dp[j][j+i] = min(dp[j][j+i], 2);
			}
		}
//		for (int i = 0; i < n; i++, puts("")) {
//			for (int j = 0; j < n; j++)
//				printf("%d ", dp[i][j]);
//		}
//		printf("%d\n", dp[0][n-1]);
		
		printf("Case %d: ", ++cases);
		if (dp[0][n-1] == 2)
			puts("Valid, Multiple");
		else if (dp[0][n-1] == 1)
			puts("Valid, Unique");
		else if (dp[0][n-1] == 0)
			puts("Invalid");
	}
	return 0;
}
/*
3
aaabba
aabb
bbababba
*/
