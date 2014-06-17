#include <stdio.h>

int main() {
	int n, s, d, a, b;
	scanf("%d", &n);
	while(n--) {
		scanf("%d %d", &s, &d);
		a = (s+d);
		b = (s-d);
		if(a < 0 || b < 0 || a%2 == 1 || b%2 == 1)
			puts("impossible");
		else
			printf("%d %d\n", a/2, b/2);
	}
    return 0;
}
