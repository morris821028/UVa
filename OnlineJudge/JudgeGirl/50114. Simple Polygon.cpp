#include <stdio.h>
 
int main() {
	int ax, ay, bx, by;
	int cx, cy, dx, dy;
	scanf("%d %d %d %d", &ax, &ay, &bx, &by);
	scanf("%d %d %d %d", &cx, &cy, &dx, &dy);
	
	printf("%d\n%d\n", (cx-ax + cy-ay)*2,
					   (cx-ax)*(cy-ay)-(dx-ax)*(cy-dy)-(cx-bx)*(by-ay));
    return 0;
}
