#include <stdio.h>
#include <math.h>
struct Point {
	int x, y, z;
}T[5001];
int main() {
	int n = 0, x, y, z;	
	while(scanf("%d %d %d", &x, &y, &z) == 3) {
		if(x == 0 && y == 0 && z == 0)	break;
		T[n].x = x, T[n].y = y, T[n].z = z;
		n++;
	}
	int D[10] = {0}, i, j;
	for(i = 0; i < n; i++) {
		int min = 0xfffffff;
		for(j = 0; j < n; j++) {
			if(i == j)	continue;
			int tmp = sqrt((T[i].x-T[j].x)*(T[i].x-T[j].x)+
			(T[i].y-T[j].y)*(T[i].y-T[j].y)+
			(T[i].z-T[j].z)*(T[i].z-T[j].z));
			if(min > tmp)	min = tmp;
		}
		if(min <= 9)
			D[min]++;
	}
	for(i = 0; i <= 9; i++)
		printf("%4d", D[i]);
	puts("");
    return 0;
}
