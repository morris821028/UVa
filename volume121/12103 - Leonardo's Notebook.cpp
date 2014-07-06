// http://m.blog.csdn.net/blog/a601025382s/9817917
#include <stdio.h>

int main() {
	int testcase;
	char s[1024];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s", s);
		int cnt[32] = {}, used[32] = {};
		for(int i = 0; i < 26; i++) {
			if(used[i])	continue;
			used[i] = 1;
			int c = 1, j = i;
			while(s[j] - 'A' != i)
				c++, j = s[j] - 'A', used[j] = 1;
			cnt[c]++;
		}
		int ret = 1;
		for(int i = 0; i <= 26; i += 2)
			ret &= cnt[i]%2 == 0;
		puts(ret ? "Yes" : "No");
	}
	return 0;
}
