#include <stdio.h>

int main() {
	char s1[32], s2[32];
	while (scanf("%s %s", s1, s2) == 2) {
		int i, j, ret = 0;
		for (i = 0; s2[i]; i++) {
			int ok = 1;
			for (j = 0; s1[j]; j++)
				ok &= s1[j] == s2[i+j];
			ret += ok;
		}
		printf("%d\n", ret);
	}
	return 0;
}
