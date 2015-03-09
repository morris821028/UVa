#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

#define MAXN 10000005
char s[MAXN];
int N;
//short dp[MAXN][2];
int main() {
	while (scanf("%d", &N) == 1 && N) {
		scanf("%s", s);
//		memset(dp, 0, sizeof(dp));
//		dp[N][1] = 0x3f3f3f3f;
//		for (int i = N - 1; i >= 0; i--) {
//			if (s[i] == '0') {
//				dp[i][0] = dp[i+1][0] + 1;
//				dp[i][1] = min(dp[i+1][0]+1, dp[i+1][1]);
//			} else {
//				dp[i][0] = min(dp[i+1][0], dp[i+1][1]+1);
//				dp[i][1] = dp[i+1][1] + 1;
//			}
//		}
		int p0 = 0, p1 = 0x3f3f3f3f, p2, p3;
		for (int i = N - 1; i >= 0; i--) {
			if (s[i] == '0') {
				p2 = p0 + 1;
				p3 = min(p0+1, p1);
			} else {
				p2 = min(p0, p1+1);
				p3 = p1 + 1;
			}
			p0 = p2, p1 = p3;
		}
		printf("%d\n", min(p0, p1));
	}
	return 0;
}
