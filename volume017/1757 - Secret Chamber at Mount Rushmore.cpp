#include <bits/stdc++.h> 
using namespace std;
const int MAXC = 26;
int main() {
	int n, m;
	while (scanf("%d %d", &m, &n) == 2) {
		static int f[MAXC][MAXC];
		memset(f, 0, sizeof(f));
		for (int i = 0; i < MAXC; i++)
			f[i][i] = 1;
		for (int i = 0; i < m; i++) {
			char s1[8], s2[8];
			scanf("%s %s", s1, s2);
			f[s1[0]-'a'][s2[0]-'a'] = 1;
		}
		
		for (int k = 0; k < MAXC; k++) {
			for (int i = 0; i < MAXC; i++) {
				for (int j = 0; j < MAXC; j++)
					f[i][j] |= f[i][k]&f[k][j];
			}
		}

		for (int it = 0; it < n; it++) {
			char s1[64], s2[64];
			scanf("%s %s", s1, s2);
			int valid = strlen(s1) == strlen(s2);
			for (int i = 0; s1[i] && valid; i++)
				valid &= f[s1[i]-'a'][s2[i]-'a'];
			puts(valid ? "yes" : "no");
		}
	}
	return 0;
}
/*
9 5
c t
i r
k p
o c
r o
t e
t f
u h
w p
we we
can the
work people
it of
out the

3 3
a c
b a
a b
aaa abc
abc aaa
acm bcm
*/
