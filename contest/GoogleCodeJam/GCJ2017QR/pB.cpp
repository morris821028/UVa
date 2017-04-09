#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	uint64_t N;
	scanf("%d", &testcase);
	while (testcase--) {
		char s[1024];
		scanf("%s", s);
		sscanf(s, "%llu", &N);
		int n = strlen(s);
		uint64_t ret = 0;
		int begin_small = 0;
		for (int i = 0; i < n; i++) {
			int prev = ret%10;
			int st = begin_small ? 9 : (s[i]-'0');
			for (int j = st; j >= prev; j--) {
				uint64_t test = ret;
				for (int k = i; k < n; k++)
					test = test*10 + j;
				if (test <= N) {
					if (!begin_small && j != s[i]-'0')
						begin_small = 1;
					ret = ret*10 + j;
					break;
				}
			}
		}
		printf("Case #%d: %llu\n", ++cases, ret);
	}
	return 0;
}
/*
4
132
1000
7
111111111111111110
*/

