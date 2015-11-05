#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#define MAXS 1<<20
char S[MAXS];
int main() {
	int n = 0;
	char cmd[16], s1[4], s2[4];
	scanf("%s", S);
	n = strlen(S);
	while (scanf("%s", cmd) == 1) {
		if (!strcmp(cmd, "end"))
			break;
		if (!strcmp(cmd, "replace")) {
			scanf("%s %s", s1, s2);
			for (int i = 0; S[i]; i++)
				if (S[i] == s1[0])
					S[i] = s2[0];
		} else if (!strcmp(cmd, "remove")) {
			scanf("%s", s1);
			n = 0;
			for (int i = 0; S[i]; i++) {
				if (S[i] != s1[0])
					S[n++] = S[i];
			}
			S[n] = '\0';
		} else if (!strcmp(cmd, "addhead")) {
			scanf("%s", s1);
			S[n+1] = '\0';
			for (int i = n-1; i >= 0; i--)
				S[i+1] = S[i];
			S[0] = s1[0];
			n++;
		} else if (!strcmp(cmd, "addtail")) {
			scanf("%s", s1);
			S[n+1] = '\0', S[n] = s1[0];
			n++;
		} else {
			printf("invalid command %s\n", cmd);
			exit(0);
			assert(false);
		}
	}
	puts(S);
	return 0;
}
