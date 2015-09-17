#include <stdio.h>

int main() {
	int A[3], B[3];
	const int p[9] = {0, 0, 0, 200, 1000, 4000, 10000, 40000, 200000};
	for (int i = 0; i < 3; i++) 
		scanf("%d", &A[i]);
	for (int i = 0; i < 3; i++)
		scanf("%d", &B[i]);
	int sum = 0, x;
	while (scanf("%d", &x) == 1) {
		for (int i = 0; i < 3; i++) {
			if (x == A[i])
				sum += 2000000;
		}
		for (int i = 0; i < 3; i++) {
			int base = 1e+8;
			for (int j = 8; j >= 3; j--, base /= 10) {
				if (x%base == B[i]%base) {
					sum += p[j];
					break;
				}				
			}
		}
	}
	printf("%d\n", sum);
	return 0;
}
