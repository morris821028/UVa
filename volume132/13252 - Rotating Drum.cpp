#include <bits/stdc++.h> 
using namespace std;

const int MAXM = 131072;
#define MAXL (MAXM>>5)+1
#define GET(x) (mark[x>>5]>>(x&31)&1)
#define SET(x) (mark[x>>5] |= 1<<(x&31))
int mark[MAXL];
char s[MAXM];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		memset(mark, 0, sizeof(mark));
		int tot = 1;
		for (int i = 0; i < m; i++)
			tot *= n;
		for (int i = 0; i < m; i++)
			s[i] = 'A';
		int st = 0, ed = tot-1;
		int idx = 1, pos = 0;
		memset(mark, 0, sizeof(mark));
		for (int i = 1; i < m; i++) {
			ed = ed*n - (n-1)*tot;
			SET(ed);
		}
		SET(st);
		for (; idx < tot; ) {
			st = st*n - (s[pos]-'A')*tot;
			int fill = -1;
			for (int i = 0; i < n; i++) {
				if (!GET(st+i)) {
					fill = i, st += i;
					break;
				}
			}
			if (fill == -1)
				break;
			SET(st), s[pos+m] = fill+'A', pos++;
		}
		s[pos+m] = '\0';
		puts(s);
	}
	return 0;
}
/*
4  2
2  3
1  5

AABACADBBCBDCCDD
AAABABBB
AAAAA
*/
