#include <stdio.h>

int main() {
	int t, cA, cB;
	int A = 0, B = 0;
	while (scanf("%d%d%d", &t, &cA, &cB) == 3) {
		A = cA + (A < t ? t : A);
		B = cB + (B < A ? A : B);
		printf("%d\n", B);
	}
	return 0;
}
