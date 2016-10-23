#include <bits/stdc++.h>
using namespace std;

string int2str(unsigned long long x) {
	stringstream sin;
	sin << x;
	return sin.str();
}
int main() {
	unsigned long long dp[100] = {0, 1, 1, 2, 3};
	const int n = 92;
	string strf[100];
	int g[100][100] = {};
	for (int i = 2; i <= 92; i++)
		dp[i] = dp[i-1] + dp[i-2];
	
	for (int i = 1; i <= 92; i++)
		strf[i] = int2str(dp[i]);
	
	set<string> S;
	for (int i = 1; i <= 92; i++) {
		for (int j = 1; j <= 92; j++) {
			if (i == j)
				continue;
			string tmp = strf[i] + strf[j];
			if (S.count(tmp))
				g[i][j] = 1;
			else
				S.insert(tmp);
		}
	}
	static char s[1048576];
	while (scanf("%s", s) == 1) {
		int m = 0;
		for (int i = 0; s[i]; i++) {
			if (isdigit(s[i]))
				s[m++] = s[i];
		}
		s[m] = '\0';
		
		int ret = 0;
		
		int first[100], last[100];
		memset(first, -1, sizeof(first));
		memset(last, -1, sizeof(last));
		for (int i = 1; i <= 92; i++) {
			int idx = 0, len = strf[i].length();
			const char *sptr = strf[i].c_str();
			for (int j = 0; j < m && idx < len; j++) {
				if (sptr[idx] == s[j]) {
					idx++;
					if (idx == len) {
						first[i] = j;
						break;
					}
				}
			}
			
			idx = len-1;
			for (int j = m-1; j >= 0; j--) {
				if (sptr[idx] == s[j]) {
					idx--;
					if (idx == -1) {
						last[i] = j;
						break;
					}
				}
			}
		}
		
		for (int i = 1; i <= 92; i++) {
			if (first[i] == -1)
				continue;
			for (int j = 1; j <= 92; j++) {
				if (i == j || last[j] == -1)
					continue;
				if (first[i] <= last[j] && g[i][j] == 0) {
					ret += first[i] < last[j] && g[i][j] == 0;	
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

