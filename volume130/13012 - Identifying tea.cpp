#include <stdio.h>

int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		int x, ret = 0;
		for (int i = 0; i < 5; i++)
			scanf("%d", &x), ret += n == x;
		printf("%d\n", ret);
	}
	return 0;	
}
