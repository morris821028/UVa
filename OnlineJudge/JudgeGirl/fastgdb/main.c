#include <stdio.h> 

int main() {
	int x, y, z;
	while (scanf("%d", &y) == 1) {
		x = 100;
		z = x / y;
		printf("%d / %d = %d\n", x, y, z);
	}
	return 0;
}
