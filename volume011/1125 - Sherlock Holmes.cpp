#include <stdio.h>
#include <stdlib.h> 
#include <set>
#include <algorithm>
using namespace std;

int main() {
	int n, m, A[32767];
	while (scanf("%d %d", &n, &m) == 2) {
		int w, b, wsum = 0, bsum = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &w, &b);
			wsum += w, bsum += b;
			A[i] = w;
		}
		if (wsum == bsum || n%2 != 0) {
			puts("No solution");
			continue;
		}
		char major = 'W';
		if (wsum < bsum) {
			major = 'B';
			wsum = bsum;
			for (int i = 0; i < n; i++)
				A[i] = m - A[i];
		}
		set<int> dp[32767];
		set<int>::iterator it;
		dp[0].insert(0);
		for (int i = 0; i < n; i++) {
			int w = A[i];
			for (int j = min(i, n/2 - 1); j >= 0; j--) {
				for (it = dp[j].begin(); it != dp[j].end(); it++)
					dp[j+1].insert((*it) + w);
			}
		}
		
		int ret = -1;
		int half = n/2 * m / 2;
		for (it = dp[n/2].begin(); it != dp[n/2].end(); it++) {
			if (*it <= wsum/2 && *it > half)
				ret = max(ret, *it);
		}
		if (ret < 0) {
			puts("No solution");
		} else {
			printf("%c %.2lf\n", major, ret * 100.0 / (n/2 * m));
		}
	}
	return 0;
}
