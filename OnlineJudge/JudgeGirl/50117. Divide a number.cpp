#include <stdio.h>

int main() {
	char c;
	int k = getchar() - '0';
	int x = 0, lead = 0;
	getchar();

	int t[10][100];
	for (int i = 1; i < 10; i++) {
		for (int j = 0; j < 100; j++)
			t[i][j] = j%i;
	}

	while ((c = getchar()) != EOF) {
		if (c > ' ') {
			x = x*10 + c-'0';
			if (lead || x/k) {
				putchar(x/k + '0'), putchar('\n');
				lead = 1;
			}
		}
		x = t[k][x];
	}
	if (!lead)
		puts("0");
	return 0;
}
