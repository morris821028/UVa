#include <stdio.h> 
#include <string.h>
#include <algorithm> 
using namespace std;

char s[32767], sub[128][128];
int slen[128];
int main() {
	int testcase, n, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s %d", s, &n);
		int m = strlen(s);
		for(int i = 0; i < n; i++) {
			scanf("%s", sub[i]);
			slen[i] = strlen(sub[i]);
			slen[n + i] = slen[i];
			for(int j = 0, k = slen[i] - 1; k >= 0; j++, k--)
				sub[n + i][j] = sub[i][k];
			sub[n + i][slen[i]] = '\0';
		}
		n *= 2;
		int dp[32767] = {};
		for(int i = 0; i <= m; i++)
			dp[i] = 0x3f3f3f3f;
		dp[0] = 0;
		for(int i = 0; i < m; i++) {
			if(dp[i] == 0x3f3f3f3f)
				continue;
			for(int j = 0; j < n; j++) {
				int f = 1;
				for(int k = 0; sub[j][k] && f; k++)
					f &= sub[j][k] == s[i + k];
				if(f)
					dp[i + slen[j]] = min(dp[i + slen[j]], dp[i] + 1);
			}
		}
		printf("Set %d: ", ++cases);
		if(dp[m] == 0x3f3f3f3f)
			puts("Not possible.");
		else
			printf("%d.\n", dp[m]);
	}
	return 0;
}
