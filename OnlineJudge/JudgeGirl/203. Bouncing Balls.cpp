#include <stdio.h>
#define swap(x, y) {int t; t = x, x = y, y = t;}
int main() {
	int H, W, T;
	int x1, y1, x2, y2;
	int dx1, dy1, dx2, dy2;
	while (scanf("%d %d", &H, &W) == 2) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		scanf("%d %d %d %d", &dx1, &dy1, &dx2, &dy2);
		scanf("%d", &T);
		while (T--) {
			if (x1 == 1 || x1 == H)
				dx1 = -dx1;
			if (y1 == 1 || y1 == W)
				dy1 = -dy1;
			if (x2 == 1 || x2 == H)
				dx2 = -dx2;
			if (y2 == 1 || y2 == W)
				dy2 = -dy2;
			if (x1 == x2 && y1 == y2) {
				swap(dx1, dx2);
				swap(dy1, dy2);
			}
			x1 += dx1, y1 += dy1;
			x2 += dx2, y2 += dy2;
		}
		printf("%d\n%d\n", x1, y1);
		printf("%d\n%d\n", x2, y2);
	}
	return 0;
}
