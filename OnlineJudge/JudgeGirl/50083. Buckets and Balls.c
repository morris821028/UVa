#include <stdio.h>

int main() {
	int cA, cB, r, w;
	scanf("%d%d%d", &cA, &cB, &r);
	if (r == 0) {
		while (scanf("%d", &w) == 1) {
			if (cA >= w)
				cA -= w;
			else if (cB >= w)
				cB -= w;
			printf("%d %d\n", cA, cB);
		}
	} else {
		while (scanf("%d", &w) == 1) {
			if (cA <= cB) {
				if (cA >= w)
					cA -= w;
				else if (cB >= w)
					cB -= w;
			} else {
				if (cB >= w)
					cB -= w;
				else if (cA >= w)
					cA -= w;
			}
			printf("%d %d\n", cA, cB);
		}
	}
	return 0;
}
