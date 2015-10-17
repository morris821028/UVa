#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sim(char *s1, char *s2) {
	int n = strlen(s1), m = strlen(s2);
	if (abs(n-m) > 1)	return 0;
	if (n == m) {
		int diff = 0, diff2 = 0;
		for (int i = 0; i+1 < n; i++) {
			if (s1[i+1] == s2[i] && s1[i] == s2[i+1] && s1[i] != s1[i+1])
				diff++;
		}
		for (int i = 0; i < n; i++)
			diff2 += s1[i] != s2[i];
		if (diff == 0 && diff2)	return 0;
		return diff <= 1;
	}
#define swap(x, y, TYPE) {TYPE t; t = x, x = y, y = t;}
	if (n > m) {
		swap(n, m, int);
		swap(s1, s2, char*);
	}
	int i = 0, j = 0, diff = 0;
	while (i < n || j < m) {
		if (s1[i] != s2[j])	diff++, j++;
		else	i++, j++;
	}
	return diff <= 1;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		char s1[128], s2[128];
		scanf("%s %s", s1, s2);
		puts(sim(s1, s2) ? "yes" : "no");
	}
	return 0;
}
