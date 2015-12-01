#include <bits/stdc++.h>
using namespace std;

int main() {
	int n, m;
	int A[5] = {1, 10, 100, 1000, 10000};
	while (scanf("%d %d", &n, &m) == 2) {
		int B, x, ret = 0;
		for (int i = 0; i < m; i++) {
			int sum = 0, f;
			scanf("%d %d", &B, &f), sum = f;
			for (int j = 1; j < n; j++)
				scanf("%d", &x), sum += x;
			if (sum <= B) {
				for (int j = 4; j >= 0; j--) {
					if (sum - f + A[j] <= B) 
						ret += A[j] - f, j = -1;
				}
			} else {
				for (int j = 4; j >= 0; j--) {
					if (sum - f + A[j] <= B)
						ret += A[j], j = -1;
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}

