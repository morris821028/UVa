#include <stdio.h>
#include <string.h>

int main() {
	int testcase, cases = 0;
	char s[100005];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s", s);
		int n = strlen(s);
		int ret = 0;
		int p, q, r;
#define mod 1000000007
		q = n / 2, p = q - 1;
		for(int i = 0, j = n&1; i < n; i++, j = !j) {
			if(j) {
				if(n - q > p)
					r = (s[q] - '0'), q++;
				else
					r = (s[p] - '0'), p--;
			} else {
				if(s[p] > s[q])
					r = (s[p] - '0'), p--;
				else
					r = (s[q] - '0'), q++;
			}
			ret = (ret << 1) + r;
			if(ret >= mod)
				ret %= mod;
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
3
00000
0101101
100
*/
