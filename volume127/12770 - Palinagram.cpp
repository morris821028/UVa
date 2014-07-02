#include <stdio.h> 
#include <algorithm>
using namespace std;

int main() {
	char s[1024], buf[1024];
	while(scanf("%s", s) == 1 && s[0] != '#') {
		int cnt[128] = {};
		for(int i = 0; s[i]; i++)
			cnt[s[i]]++;
		int f = 0, n = 0;
		for(int i = 127; i >= 0; i--) {
			if(cnt[i]&1) {
				if(f == 0) f = 1;
				else {
					buf[n++] = i;
				}
			} 
		}
		sort(buf, buf + n);
		buf[n] = '\0';
		puts(buf);
	}
	return 0;
}
/*
ddc
aaab
#
*/
