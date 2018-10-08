#include <stdio.h>

int main() {
	int a, b, c, d, h;
	scanf("%d %d %d %d %d", &a, &b, &h, &c, &d);
	printf("%d\n", a*b*h/(a*b-c*d));
	return 0;
}
