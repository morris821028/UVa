#include <stdio.h>
#include <string.h>
int mpow(int x, int y) {
	int ret = 1;
	while (y) {
		if (y&1)	ret *= x;
		y >>= 1, x = x * x;
	}
	return ret;
}
int main() {
	scanf("%*d");
	char buf[32];
	int n;
	while (scanf("%d", &n) == 1) {
		sprintf(buf, "%d", n);
		int m = strlen(buf), sum = 0;
		for (int i = 0; i < m; i++)
			sum += mpow(buf[i] - '0', m);
		puts("Not Armstrong" + (sum == n ? 4 : 0));
	}
	return 0;
}
