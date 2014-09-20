#include <stdio.h> 

int main() {
	int testcase, n, m, x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		int ret = 1;
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			ret &= x >= n;
		}
		puts(ret ? "YEEES!!! INKER!" : "NOOOO!!! JACKY XX!");
	}
	return 0;
}
