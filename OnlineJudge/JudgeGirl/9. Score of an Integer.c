#include <stdio.h>

int main() {
	int x;
	scanf("%d", &x);
	if (x <= 0) {
		printf("-100\n");
	} else {
		int s = 0;
		if (x%3 == 0)	s += 3;
		if (x%5 == 0)	s += 5;
		if (x >= 100 && x <= 200)
			s += 50;
		else
			s -= 50;
		printf("%d\n", s);
	}
	return 0;
}
