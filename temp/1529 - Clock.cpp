#include <stdio.h> 
/*
	x = 12y
	x - y = 60
	=> y = 60 / 11, x = 720 / 11
*/
int main() {
	double A[60] = {};
	for (int i = 1; i < 60; i++)
		A[i] = A[i-1] + 720.0 / 11.0;
		
	puts("Program 3 by team X");
	puts("Initial time  Final time  Passes");
	int h1, h2, m1, m2;
	while (scanf("%d %d %d %d", &h1, &m1, &h2, &m2) == 4) {
		int ret = 0, v1, v2;
		v1 = h1 * 60 + m1;
		v2 = h2 * 60 + m2;
		if (v1 > v2)	v2 += 720;
		for (int i = 0; i < 60; i++) {
			if (A[i] >= v1 && A[i] <= v2)
				ret ++;
		}
		printf("       %02d:%02d       %02d:%02d %7d\n", h1, m1, h2, m2, ret);
	}
	
	puts("End of program 3 by team X");
	return 0;
}
