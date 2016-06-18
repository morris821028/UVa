#include <bits/stdc++.h>
using namespace std;
const int MAXN = 131072;
int main() {
	int testcase;
	static char s1[MAXN], s2[MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %s", s1, s2);
		int n = strlen(s1), m = strlen(s2);
		int p = 0, q = 0;
		while (p < n && q < m) {
			if (s1[p] == s2[q])
				p++, q++;
			else
				p++;
		}
		puts(q == m ? "YES" : "NO");
	}
	return 0;
}

