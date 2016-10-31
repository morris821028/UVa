#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isValid(char *s) {
	char s1[16], s2[16];
	if (strlen(s) != 7)
		return 0;
	if (sscanf(s, "%[^-]-%[^-]", s1, s2) != 2)
		return 0;
	if (!(strlen(s1) == 2 && strlen(s2) == 4)
		&& !(strlen(s1) == 3 && strlen(s2) == 3))
		return 0;
	strcat(s1, s2);
	if (strlen(s1) != 6)
		return 0;
	// rule 1
	for (int i = 0; s1[i]; i++) {
		if (!isalnum(s1[i]))
			return 0;
	}
	// rule 2
	int sum = 0;
	for (int i = 0; s1[i]; i++) {
		if (isdigit(s1[i]))
			sum += s1[i] - '0';
	}
	if (sum%7 == 0)
		return 0;
	// rule 3
	int mark[128] = {};
	for (int  i = 0; s1[i]; i++) {
		if (mark[s1[i]] > 1)
			return 0;
		mark[s1[i]]++;
	}
	// rule 4
	if (strstr(s, "44"))
		return 0;
	return 1 + (strlen(s2) == 3);
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int m1 = 0, m2 = 0;
		char ret1[64][16], ret2[64][16];
		for (int i = 0; i < n; i++) {
			char s[16];
			scanf("%s", &s);
			int type = isValid(s);
			if (type) {
				if (type == 1)
					strcpy(ret1[m1], s), m1++;
				if (type == 2)
					strcpy(ret2[m2], s), m2++;
			}
		}
		for (int i = 0; i < m1; i++) {
			int idx = i;
			for (int j = i; j < m1; j++) {
				if (strcmp(ret1[j], ret1[idx]) < 0)
					idx = j;
			}
			puts(ret1[idx]);
			strcpy(ret1[idx], ret1[i]);
		}
		for (int i = 0; i < m2; i++) {
			int idx = i;
			for (int j = i; j < m2; j++) {
				if (strcmp(ret2[j], ret2[idx]) < 0)
					idx = j;
			}
			puts(ret2[idx]);
			strcpy(ret2[idx], ret2[i]);
		}
	}
	return 0;
}

