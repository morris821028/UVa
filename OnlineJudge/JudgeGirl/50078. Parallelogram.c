#include <stdio.h>

int main() {
	int ax, ay, bx, by, cx, cy;
	scanf("%d%d%d%d%d%d", &ax, &ay, &bx, &by, &cx, &cy);
	int dx, dy, ex, ey, fx, fy;
	dx = bx + cx - ax, dy = by + cy - ay;
	ex = ax + cx - bx, ey = ay + cy - by;
	fx = ax + bx - cx, fy = ay + by - cy;
	printf("%d\n%d\n%d\n%d\n%d\n%d\n", dx, dy, ex, ey, fx, fy);
	return 0;
}
