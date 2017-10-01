#include <stdio.h>
#include <limits.h>

int main() {
	int n, x;
	while (scanf("%d", &n) == 1) {
		int mn = INT_MAX, mx = INT_MIN;
		for (int i = 0; i < n; i++) {
			int ret = scanf("%d", &x);
			if (ret == EOF) {
				printf("%d\n", mn);
				return 0;
			}
			mn = x < mn ? x : mn;
			mx = x > mx ? x : mx;
		}
		printf("%d\n", mx);
	}
	return 0;
}
