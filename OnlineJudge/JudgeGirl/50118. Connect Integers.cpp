#include <stdio.h>
#include <string.h>

int main() {
	char s[16];
	int mx = 0, sum = 0;
	int last = -1;
	while (scanf("%s", s) == 1) {
		int w = strlen(s);
		if (last == s[0])
			sum += w;
		else
			sum = w;

		if (sum > mx)
			mx = sum;
		last = s[w-1];
	}
	printf("%d\n", mx);
	return 0;
}
