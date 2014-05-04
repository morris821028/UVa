#include <stdio.h>

int main() {
	int n, m = 0;
	scanf("%d", &n);
	while(n--) {
		int a, b, length, width, depth, weight;
		scanf("%d.%d", &a, &b);
		length = a * 100 + b;
		scanf("%d.%d", &a, &b);
		width = a * 100 + b;
		scanf("%d.%d", &a, &b);
		depth = a * 100 + b;
		scanf("%d.%d", &a, &b);
		weight = a * 100 + b;
		int f = 1;
		f &= (length <= 5600 && width <= 4500 && depth <= 2500) || length + width + depth <= 12500;
		f &= weight <= 700;
		printf("%d\n", f);
		m += f;
	} 
	printf("%d\n", m);
	return 0;
}
