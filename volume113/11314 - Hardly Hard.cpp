#include <stdio.h>
#include <math.h>
int main() {
	int n;
	double ax, ay, bx, by;
	double cx, cy, dx, dy;
	scanf("%d", &n);
	while(n--) {
		scanf("%lf %lf %lf %lf", &ax, &ay, &bx, &by);
		cx = -bx, cy = by;
		dx = ax, dy = -ay;
		printf("%.3lf\n", sqrt((ax-bx)*(ax-bx)+(ay-by)*(ay-by))+sqrt((cx-dx)*(cx-dx)+(cy-dy)*(cy-dy)));
	}
    return 0;
}
