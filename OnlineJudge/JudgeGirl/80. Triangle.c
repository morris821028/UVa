#include <stdio.h>
#define SQR(x) ((x)*(x))
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int x1, x2, x3, y1, y2, y3;
		scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3);
		int a, b, c;
		a = SQR(x1 - x2) + SQR(y1 - y2);
		b = SQR(x2 - x3) + SQR(y2 - y3);
		c = SQR(x1 - x3) + SQR(y1 - y3);
		if (a == b || b == c || c == a) {
			puts("isosceles");
		} else if (a == b+c || b == c+a || c == b+a) {
			puts("right");
		} else if (a > b+c || b > c+a || c > b+a) {
			puts("obtuse");
		} else {
			puts("acute");
		}
	}
	return 0;
}
