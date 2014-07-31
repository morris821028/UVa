#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <vector>
#include <algorithm>
using namespace std;
int dp[65536], ardp[65536], from[65536], n, bb;
char s[65536];
void travel(int i) {
	if(i == 0)	return;
	if(ardp[i] >= 129) {
		travel(from[i]);
		printf("%c%c", ardp[i], s[i]), bb += 2;
	} else {
		travel(from[i]);
		printf("%c", ardp[i]), bb++;
		for(int j = ardp[i]; j >= 0; j--)
			printf("%c", s[i - j]), bb++;
	}
}
int main() {
	int idx = 1;
	char c;
	while((c = getchar()) != EOF)
		s[idx++] = c;
	{
		n = strlen(s+1);
		assert(n < 65536);
		memset(dp, 63, sizeof(dp));
		dp[0] = 0;
		for(int i = 0; i <= n; i++) {
			int cnt = 0;
			for(int j = i+1; j <= n; j++) {
				if(s[j] == s[i+1]) {
					cnt++;
					if(cnt + 127 > 255)
						break;
					if(cnt >= 2) {
						if(dp[j] > dp[i] + 2)
							ardp[j] = cnt + 127, from[j] = i;
						dp[j] = min(dp[j], dp[i] + 2);
					}
				} else
					break;
			}
			cnt = 0;
			for(int j = i+1; j <= n; j++) {
				cnt++;
				if(cnt - 1 > 127)	break;
				if(dp[j] > dp[i] + cnt + 1)
					ardp[j] = cnt - 1, from[j] = i;
				dp[j] = min(dp[j], dp[i] + cnt + 1);
			}
		}
		bb = 0;
		travel(n);
//		printf("bytes %d\n", bb);
	}
	return 0;
}

/*
aaaaaaaarstqahbbbbbbb
aaaaaaaaaa
abcdefghij
aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122122
*/
