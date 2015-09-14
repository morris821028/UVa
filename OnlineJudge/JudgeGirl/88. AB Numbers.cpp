#include <stdio.h>

int main() {
	char s1[8], s2[8];
	while (scanf("%s %s", s1, s2) == 2) {
		int i, A = 0, B = 0;
		int cnt[10] = {};
		for (i = 0; s1[i]; i++)
			cnt[s1[i]-'0']++;
		for (i = 0; s2[i]; i++) {
			A += s1[i] == s2[i];
			B += cnt[s2[i]-'0'];
			if (cnt[s2[i]-'0'])
				cnt[s2[i]-'0']--;
		}
		printf("%dA%dB\n", A, B-A);
	}
	return 0;
}
