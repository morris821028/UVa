#include <bits/stdc++.h>
using namespace std;
int MinExp(const char *s, const int slen) {
	int i = 0, j = 1, k = 0, x, y, tmp;
	while (i < slen && j < slen && k < slen) {
		x = i + k;
		y = j + k;
		if (x >= slen)	x -= slen;
		if (y >= slen)	y -= slen;
		if (s[x] == s[y]) {
			k++;
		} else if (s[x] > s[y]) {
			i = j+1 > i+k+1 ? j+1 : i+k+1;
			k = 0;
			tmp = i, i = j, j = tmp;
		} else {
			j = i+1 > j+k+1 ? i+1 : j+k+1;
			k = 0;
		}
	}
	return i;
}
int main() {
	int testcase;
	char s[65536];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s", s);
		int n = strlen(s);
		printf("%d\n", MinExp(s, n)+1);
	}
	return 0;
}

