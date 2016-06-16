#include <bits/stdc++.h>
using namespace std;

static char buf[262144], *p;
void printInt(int x) {
    static char stk[16];
    int idx = 0;
    static char m[10] = {0, 1, 5, 3, 4, 2, 9, 7, 8, 6};
    if (!x)	
        stk[idx++] = '0';
    while (x)
        stk[idx++] = m[x%10] + '0', x /= 10;
    while (idx)
        *p = stk[--idx], p++;
}
int main() {
	char s[131072];
	while (scanf("%s", s) == 1) {
		int used[128] = {}, t = 0;
		p = buf;
		for (int i = 0; s[i]; i++) {
			int u;
			if (used[s[i]] == 0) {
				used[s[i]] = ++t;
			}
			u = used[s[i]];
			printInt(u);
		}
		*p = '\0';
		puts(buf);
	}
	return 0;
}

