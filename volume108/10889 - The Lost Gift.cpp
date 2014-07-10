#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;

int main() {
	int R, B;
	while(scanf("%d %d", &R, &B) == 2 && R+B) {
		int sqr = (int)sqrt(8 * R + 1);
		// 2 * (C(n, 2) + C(m, 2)) = C(n+m, 2)
		// m^2 - (2n + 1) m + n^2 - n = 0
		// m = [(2n + 1) +/- sqrt(8n+1)] / 2
		if(sqr * sqr == 8 * R + 1 && sqr%2) {
			int r1 = (2 * R + 1 - sqr)/2;
			int r2 = (2 * R + 1 + sqr)/2;
			int f = 0, prev = -1;
			if(r1 >= B && (r1 - B)/(double)r1 <= 0.3)
				printf("%d", r1 - B), f = 1, prev = r1;
			if(r2 >= B && (r2 - B)/(double)r2 <= 0.3) {
				if(prev != r2) {
					if(f)	putchar(' ');
					printf("%d", r2 - B), f = 1;
				}
			}
			if(!f)
				printf("No. of black balls invalid");
			puts("");
		} else
			puts("No. of red balls invalid");
	}
	return 0;
}
