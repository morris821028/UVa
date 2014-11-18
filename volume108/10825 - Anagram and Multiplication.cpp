#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	int n, m;
	while (scanf("%d %d", &m, &n) == 2 && n) {
		int flag = 0;
		for (int i = 1; i < n && !flag; i++) {
			int A[10], C[10], p = 0;
			for (int j = 2; j <= m; j++)
				A[p++] = (i * j)%n;
			A[p++] = i;
			sort(A, A+p);
			for (int j = 0; j < p; j++)
				C[j] = A[j];
			do {
				int ok = 1;
				for (int j = 2; j <= m && ok; j++) {
					int B[10] = {};
					for (int k = 0; k < p; k++)
						B[k] = A[k] * m;
					for (int k = 0; k < p; k++)
						B[k+1] += B[k] / n, B[k] %= n;
					if (B[p])	ok = 0;
					sort(B, B + p);
					for (int k = 0; k < p; k++)
						ok &= B[k] == C[k];
				}
				if (ok) {
					for (int j = p - 1; j >= 0; j--)
						printf("%d%c", A[j], j ? ' ' : '\n');
					flag = 1;
					break;
				}
			} while (next_permutation(A, A+p));
		}
		if (!flag)
			puts("Not found.");
	}
	return 0;
}
/*
6 10
6 100
0 0
*/
