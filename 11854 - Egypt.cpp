#include<stdio.h>
#define Swap(x, y) {int t; t = x, x = y, y = t;}
int main() {
	int x, y, z;
	while(scanf("%d %d %d", &x, &y, &z) == 3) {
		if(x == 0 && y == 0 && z == 0)
			break;
		if(x > z)	Swap(x, z);
		if(y > z)	Swap(y, z);
		puts(x*x + y*y == z*z ? "right" : "wrong");
	}
    return 0;
}
