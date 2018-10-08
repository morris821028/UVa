#include <stdio.h>

int main() {
	char c;
	int d = 0, last = 0, zero = 0, sum = 0;
	while ((c = getchar()) != EOF) {
		if (c > ' ') {
			c -= '0';
			d++;
			last = c;
			zero += c == 0;
			sum += (d&1) ? c : -c;
		}
	}
	printf("%d\n%d\n%d\n%d\n", d, last%2 == 0, zero, sum%11 == 0);
	return 0;
}
