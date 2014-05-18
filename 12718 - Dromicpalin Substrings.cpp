#include <stdio.h> 
#include <string.h>

int main() {
	int testcase, cases = 0;
	char s[1024];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s", s);
		int ret = 0, n = strlen(s);
		for(int i = 0; i < n; i++) {
			int cnt[26] = {}, odd = 0;
			for(int j = i, m = 1; j < n; j++, m++) {
				cnt[s[j] - 'a']++;
				odd += cnt[s[j] - 'a']%2 ? 1 : -1;
				if(m%2 == 0 && odd == 0)
					ret++;
				else if(m%2 == 1 && odd == 1)
					ret++;
			}
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
/*
4
acmicpc
aaaaa
isyoursolutionfastenough
abbabababbaba
*/
