#include <stdio.h>
#define MAXN 100005
int main() {
	int testcase;
	char s[MAXN];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s", s);
		int pos[MAXN * 2] = {};
		int height = MAXN, ret = 0;
		for(int i = 0; s[i]; i++) {
			if(s[i] == '\\')
				pos[height] = i + 1, height--;
			else if(s[i] == '/' && pos[++height]) {
				ret += i + 1 - pos[height];
				pos[height] = 0;
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
