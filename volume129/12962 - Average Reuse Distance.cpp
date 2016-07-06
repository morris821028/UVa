#include <bits/stdc++.h>
using namespace std;

int main() {
	static char s[16777216];
	while (scanf("%s", s) == 1 && s[0] != '0') {
		int past[128];
		long long sum = 0, cnt = 0;
		memset(past, -1, sizeof(past));
		for (int i = 0; s[i]; i++) {
			int l = past[s[i]], r = i;
			int dist = 0;
			for (int j = 'a'; j <= 'z'; j++)
				dist += past[j] > l;
			if (l != -1)
				sum += dist, cnt ++;
			past[s[i]] = i;
		}
		if (cnt == 0)
			puts("NaN");
		else
			printf("%.4lf\n", (double) sum/cnt);
	}
	return 0;
}

