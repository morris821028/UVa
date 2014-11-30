#include <stdio.h> 
#include <ctype.h>
using namespace std;
#define MAXN 1024
char s[MAXN];
int dp[MAXN][MAXN], A[MAXN];
int main() {
	int K, cases = 0;
	while (scanf("%d", &K) == 1) {
		while (getchar() != '\n');
		gets(s);
		int n = 0;
		for (int i = 0; s[i]; i++) {
			if (isalpha(s[i])) {
				s[n] = tolower(s[i]);
				A[n] = i + 1;
				n++;
			}
		}
		
		int ret = -1, pos = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; i+j < n; j++) {
				int l = j, r = i+j;
				dp[l][r] = dp[l+1][r-1] + (s[l] != s[r]);
				if (dp[l][r] <= K) {
					int len = A[r] - A[l] + 1;
					if (ret < len || (ret == len && pos > A[l]))
						ret = len, pos = A[l];
				}
			}
		}
		printf("Case %d: %d %d\n", ++cases, ret, pos);
	}
	return 0;
}
/*
1
Wow, it is a Race cat!
0
abcdefg
0
Kitty: Madam, I'm adam.
*/
