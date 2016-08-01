#include <bits/stdc++.h>
using namespace std;

int edit_dist(const char *a, int la, const char *b, int lb) {
	static int dp[16][16] = {};
	memset(dp, 0x3f, sizeof(dp));
	int INF = dp[0][0];
	dp[0][0] = 0;
	for (int i = 1; i <= lb; i++) {
		for (int j = 0; j <= la; j++) {
			if (dp[i-1][j] == INF)
				continue;
			for (int k = j+1; k <= la; k++) {
				if (a[k-1] == b[i-1])
					dp[i][k] = min(dp[i][k], dp[i-1][j] + 3*(k-j-1));
				dp[i][k] = min(dp[i][k], dp[i-1][j] + 3*(k-j-1) + 5);
			}
			dp[i][j] = min(dp[i][j], dp[i-1][j]+3);
		}
	}
	int ret = INF;
	for (int i = 0; i <= la; i++)
		ret = min(ret, dp[lb][i] + (la - i)*3);
	return ret;
}
int main() {
	int n, m;
	char s[1024];
	string dict[65536];
	int cases = 0;
	while (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			dict[i] = s;
		}
		sort(dict, dict+n);
		scanf("%d", &m);
		while (getchar() != '\n');
		if (cases++)
			puts("");
		
		char *sptr = NULL, *send = NULL;
		for (int i = 0; i < m; i++) {
			while (1) {
				if (sptr == NULL) {
					fgets(s, 1024, stdin);
					sptr = s, send = s + strlen(s);
				}
				while (sptr && sptr != send && isspace(*sptr))
					putchar(*sptr), sptr++;
				if (sptr == send)	sptr = NULL;
				if (sptr && !isspace(*sptr))
					break;
			}
			char buf[16];
			int len = 0;
			for (; isalpha(*sptr); sptr++)
				buf[len++] = *sptr;
			buf[len] = '\0';
			int mn = INT_MAX, mnIdx = 0;
			for (int j = 0; j < n; j++) {
				int t = edit_dist(dict[j].c_str(), dict[j].length(), buf, len);
				if (t < mn)
					mn = t, mnIdx = j;
			}
			fputs(dict[mnIdx].c_str(), stdout);
		}
		while (sptr && sptr != send && isspace(*sptr))
			putchar(*sptr), sptr++;
	}
	return 0;
}

