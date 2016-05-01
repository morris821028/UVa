#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>
using namespace std;

char s1[1024], s2[1024];
char ret1[1024], ret2[1024];
int n;
int canSame() {
	for (int i = 0; i < n; i++) {
		if (s1[i] == '?' || s2[i] == '?')
			continue;
		if (s1[i] != s2[i])
			return 0;	
	}
	for (int i = 0; i < n; i++) {
		char x = '0';
		if (s1[i] != '?') x = s1[i];
		if (s2[i] != '?') x = s2[i];
		ret1[i] = x;
	}
	ret1[n] = '\0';
	return 1;
}
long long minDiff;
void updateSolution(char buf1[], char buf2[]) {
	long long u, v;
	sscanf(buf1, "%llu", &u);
	sscanf(buf2, "%llu", &v);
	long long t = u - v;
	if (t < 0)	t = -t;
	if (t < minDiff || (t == minDiff && strcmp(ret1, buf1) > 0) ||
		(t == minDiff && strcmp(ret1, buf1) == 0 &&
			strcmp(ret2, buf2) > 0)) {
		minDiff = t;
		strcpy(ret1, buf1);
		strcpy(ret2, buf2);
	}
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%s %s", s1, s2);
		n = strlen(s1);
		if (canSame()) {
			printf("Case #%d: %s %s\n", ++cases, ret1, ret1);
			continue;
		}
		minDiff = LONG_LONG_MAX;
		for (int i = 0; i < n; i++) {
			// C < J
			int same;
			char buf1[1024], buf2[1024];
			same = 1;
			for (int j = 0; j < i; j++) {
				if (s1[j] == '?' || s2[j] == '?') {
					if (s1[j] == '?' && s2[j] == '?')
						buf1[j] = buf2[j] = '0';
					else if (s1[j] == '?')
						buf1[j] = buf2[j] = s2[j];
					else
						buf1[j] = buf2[j] = s1[j];
					continue;
				}
				if (s1[j] != s2[j])
					same = 0;
				buf1[j] = buf2[j] = s1[j];
			}
			if (s1[i] == '9' || s2[i] == '0' || !same)
				continue;
			if (s1[i] != '?' && s2[i] != '?') {
				if (s1[i] > s2[i])
					continue;
				buf1[i] = s1[i], buf2[i] = s2[i];
			} else if (s1[i] == '?' && s2[i] == '?') {
				buf1[i] = '0', buf2[i] = '1';
			} else if (s1[i] != '?') {
				buf1[i] = s1[i], buf2[i] = s1[i]+1;
			} else {
				buf2[i] = s2[i], buf1[i] = s2[i]-1;
			}
			for (int j = i+1; j < n; j++) {
				if (s1[j] == '?')	buf1[j] = '9';
				else				buf1[j] = s1[j];
				if (s2[j] == '?')	buf2[j] = '0';
				else				buf2[j] = s2[j];
			}
			buf1[n] = '\0', buf2[n] = '\0';
			updateSolution(buf1, buf2);
		}
		
		for (int i = 0; i < n; i++) {
			// C > J
			int same;
			char buf1[1024], buf2[1024];
			same = 1;
			for (int j = 0; j < i; j++) {
				if (s1[j] == '?' || s2[j] == '?') {
					if (s1[j] == '?' && s2[j] == '?')
						buf1[j] = buf2[j] = '0';
					else if (s1[j] == '?')
						buf1[j] = buf2[j] = s2[j];
					else
						buf1[j] = buf2[j] = s1[j];
					continue;
				}
				if (s1[j] != s2[j])
					same = 0;
				buf1[j] = buf2[j] = s1[j];
			}
			if (s1[i] == '0' || s2[i] == '9' || !same)
				continue;
			if (s1[i] != '?' && s2[i] != '?') {
				if (s1[i] < s2[i])
					continue;
				buf1[i] = s1[i], buf2[i] = s2[i];
			} else if (s1[i] == '?' && s2[i] == '?') {
				buf1[i] = '1', buf2[i] = '0';
			} else if (s1[i] != '?') {
				buf1[i] = s1[i], buf2[i] = s1[i]-1;
			} else {
				buf2[i] = s2[i], buf1[i] = s2[i]+1;
			}
			for (int j = i+1; j < n; j++) {
				if (s1[j] == '?')	buf1[j] = '0';
				else				buf1[j] = s1[j];
				if (s2[j] == '?')	buf2[j] = '9';
				else				buf2[j] = s2[j];
			}
			buf1[n] = '\0', buf2[n] = '\0';
			updateSolution(buf1, buf2);
		}
		printf("Case #%d: %s %s\n", ++cases, ret1, ret2);
	}
	return 0;
}
