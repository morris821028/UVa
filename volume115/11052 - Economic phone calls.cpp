#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	int n;
	int time[1024];
	char mark[1024][4];
	while (scanf("%d", &n) == 1 && n) {
		int mm, dd, HH, MM;
		for (int i = 0; i < n; i++) {
			scanf("%d:%d:%d:%d %*s %s", &mm, &dd, &HH, &MM, mark[i]);
			time[i] = ((mm * 31 + dd) * 24 + HH) * 60 + MM;
		}
		int year[1024] = {}, cur_year;
		for (int i = 1; i < n; i++) {
			if (time[i] <= time[i-1])
				year[i] = year[i-1] + 1;
			else
				year[i] = year[i-1];
			cur_year = year[i];
		}
		int dp[1024] = {}, last = -1, trace = -1;
		// dp[i] : record i satisfy that all `+` record can trace in year[i]~cur_year
		for (int i = n - 1; i >= 0; i--) {
			if (last == -1 && year[i] == cur_year)
				dp[i] = 1; 		// record now time.
			else
				dp[i] = n - i; 	// record all after this. (init value)
			if (last == -1 && (mark[i][0] == '+' || year[i] != cur_year))
				last = i;
			if (mark[i][0] == '+')
				trace = i;
		}

		for (int i = last; i >= trace; i--) {
			for (int j = i + 1; j < n; j++) {
				if (year[i] == year[j])
					dp[i] = min(dp[i], dp[j] + 1);
				else if (time[i] >= time[j] && year[j] - year[i] == 1)
					dp[i] = min(dp[i], dp[j] + 1);
				else
					break;
				if (mark[j][0] == '+')	break;
			}
		}
//		for (int i = 0; i < n; i++)
//			printf("[%d] y %d dp %d\n", i, year[i], dp[i]);
//		printf("%d %d\n", last, trace);
		printf("%d\n", dp[trace]);
	}
	return 0;
}
