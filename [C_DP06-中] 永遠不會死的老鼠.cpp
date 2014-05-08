#include <stdio.h>

int main() {
	int a[1024], b[1024], n = 1024;
	a[1] = 1, b[1] = 0;
	for(int i = 2; i < n; i++) {
		a[i] = a[i - 1] + b[i - 1];
		b[i] = a[i - 1];
		a[i] ++;
	}
	while(scanf("%d", &n) == 1)
		printf("%d %d\n", a[n], b[n] + 1);
	return 0;
}
