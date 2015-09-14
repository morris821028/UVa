#include <stdio.h>

int main() {
	int h, w, d;
	while (scanf("%d %d %d", &h, &w, &d) == 3) {
		printf("%d\n", 2*(h*w+w*d+d*h));
		printf("%d\n", h*w*d);
	}
	return 0;
}

