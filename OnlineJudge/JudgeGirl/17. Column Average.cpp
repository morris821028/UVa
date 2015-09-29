#include <stdio.h>

int main() {
	int n, m, x;
	while (scanf("%d %d", &n, &m) == 2) {
		int C[128] = {};
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &x), C[j] += x;
		for (int i = 0; i < m; i++)
			printf("%d\n", C[i]/n);
	}
	return 0;
}

