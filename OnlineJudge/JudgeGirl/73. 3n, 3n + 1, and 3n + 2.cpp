#include <stdio.h>

int main() {
	int n, x;
	while (scanf("%d", &n) == 1) {
		int i, cnt[3] = {};
		for (i = 0; i < n; i++)
			scanf("%d", &x), cnt[x%3]++;
		printf("%d %d %d\n", cnt[0], cnt[1], cnt[2]);
	}
	return 0;
}
