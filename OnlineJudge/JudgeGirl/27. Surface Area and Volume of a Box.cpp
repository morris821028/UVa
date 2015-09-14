#include <stdio.h>

int main() {
	int a, b, c, d, e;
	while (scanf("%d %d %d %d %d", &a, &b, &c, &d, &e) == 5) {
		int s = 2*(a*b + b*c + c*a)+8*d*(a-2*e)+8*d*(b-2*e)+8*d*(c-2*e);
		int v = a*b*c-2*d*((a-2*e)*(b-2*e)+(b-2*e)*(c-2*e)+(a-2*e)*(c-2*e)); 
		printf("%d\n%d\n", s, v);
	}
	return 0;
}
