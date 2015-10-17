#include <stdio.h>
#include <string.h>
void ins_str(char s[], int pos, char c) {
	int n = strlen(s);
	s[n+1] = '\0';
	for (int i = n-1; i >= pos; i--)
		s[i+1] = s[i];
	s[pos] = c;
}
void del_str(char s[], int pos) {
	int n = strlen(s);
	for (int i = pos; i < n; i++)
		s[i] = s[i+1];
}
int main() {
	char s[1024] = "";
	char cmd[16], args[2][16];
	while (scanf("%s", cmd) == 1) {
		if (!strcmp(cmd, "insert")) {
			scanf("%s %s", args[0], args[1]);
			int pos = 0, x;
			if (!strcmp(args[0], "left")) {
				pos = 0;
			} else if (!strcmp(args[0], "right")) {
				pos = strlen(s);
			} else {
				sscanf(args[0], "%d", &x);
				pos = x-1;
			}
			ins_str(s, pos, args[1][0]);
		} else {
			scanf("%s", args[0]);
			int pos = 0, x;
			if (!strcmp(args[0], "left")) {
				pos = 0;
			} else if (!strcmp(args[0], "right")) {
				pos = strlen(s)-1;
			} else {
				sscanf(args[0], "%d", &x);
				pos = x-1;
			}
			del_str(s, pos);
		}
	}
	int n = strlen(s);
	int cnt = 1, mx = 0;
	for (int i = 1; i <= n; i++) {
		if (s[i] == s[i-1]) {
			cnt++;
		} else {
			if (cnt > mx)
				mx = cnt;
			cnt = 1;
		}
	}
	puts(s);
	cnt = 1;
	for (int i = 1; i <= n; i++) {
		if (s[i] == s[i-1]) {
			cnt++;
		} else {
			if (cnt == mx)
				printf("%c ", s[i-1]);
			cnt = 1;
		}
	}
	printf("%d\n", mx);
	return 0;
}
