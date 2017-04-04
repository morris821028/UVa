#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		char s[1024];
		scanf("%s", s);
		int len = strlen(s), n;
		sscanf(s, "%d", &n);
		long long sum = 0;
		long long t10[20] = {1}, pre = 0;
		for (int i = 1; i < 20; i++)
			t10[i] = t10[i-1]*10;
		for (int i = 0; i < len; i++) {
			int d = s[i]-'0';
			if (i != len-1) {
				int x;
				sscanf(s+i+1, "%d", &x);
				sum += d * (x+1);
				for (int j = 1; j < d; j++)
					sum += j * t10[len-i-1];
				sum += pre * 45 * t10[len-i-1];
			} else {
				sum += d;
				for (int j = 1; j < d; j++)
					sum += j;
				sum += pre * 45 * t10[len-i-1];
			}
			pre = pre*10 + d;
		}
		puts(sum%3 ? "NO" : "YES");
	}
	return 0;
}

