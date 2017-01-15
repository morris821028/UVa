#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int H, S;
		scanf("%d %d", &H, &S);
		vector< pair<int, int> > A;
		double ret = 0;
		for (int i = 0; i < S; i++) {
			char s[128];
			scanf("%s", s);
			int X = 0, Y = 0, Z = 0;
			for (int j = 0, x = 0, sign = 1, idx = 0; s[j]; j++) {
				if (isdigit(s[j]))
					x = x * 10 + s[j] - '0';
				if (s[j+1] == '\0' || !isdigit(s[j])) {
					x = x * sign;
					if (idx == 0)
						X = x;
					else if (idx == 1)
						Y = x;
					else
						Z = x;
					if (s[j] == '-')
						sign = -1;
					else
						sign = 1;
					x = 0, idx++;
				}
			}
			int l = X+Z, r = X*Y+Z;
			static const int OFF = 1024;
			static double dp[2][OFF];
			for (int i = 0; i < OFF; i++)
				dp[0][i] = dp[1][i] = 0;
			dp[0][0] = 1;
			for (int i = 0; i < X; i++) {
				int p = i&1, q = i&1^1;
				for (int j = 0; j < OFF; j++)
					dp[q][j] = 0;
				for (int j = 0; j < OFF; j++) {
					if (dp[p][j] <= 0)	continue;
					for (int k = 1; k <= Y; k++)
						dp[q][j+k] += dp[p][j]*((double) 1.f/Y);
				}
			}
			double sum = 0;
			for (int j = 0; j <= X*Y; j++) {
				if (j+Z >= H)
					sum += dp[(X-1)&1^1][j];
			}
			ret = max(ret, sum);
		}
		printf("Case #%d: %.6lf\n",++cases, ret);
	}
	return 0;
}

