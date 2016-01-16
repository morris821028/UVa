#include <stdio.h>
#include <stdlib.h>

int main() {
	int H1, M1, H2, M2;
	while (scanf("%d %d %d %d", &H1, &M1, &H2, &M2) == 4) {
		int diff = - (H1 * 60 + M1) + (H2 * 60 + M2);
		if (diff < 0)
			diff += 24 * 60;
		printf("%d %d\n", diff / 60, diff % 60);
	}
	return 0;
}
