// 918 - ASCII Mandelbrot
// WTF for testdata, I used + 0.00000001f to pass it.
#include <stdio.h> 
#include <math.h>
int main() {
	int testcase;
	double MINI, MAXI, MINR, MAXR, PRECI, PRECR;
	char CHARS[128];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s %lf %lf %lf %lf %lf %lf", CHARS, &MINI, &MAXI, &PRECI, &MINR, &MAXR, &PRECR);
		CHARS[0] = CHARS[13] = ' ';
		for(double a = MINI; a <= MAXI + 0.00000001f; a += PRECI) {
			for(double b = MINR; b <= MAXR + 0.00000001f; b += PRECR) {
				float za = 0, zb = 0, ca = b, cb = a, ta, tb;
				int i;
				for(i = 0; i < 12; i++) {	
					ta = za * za - zb * zb;
					tb = 2 * za * zb;
					za = ta + ca, zb = tb + cb;
					if(za * za + zb * zb > 4)
						break;
				}
				printf("%c", CHARS[i+1]);
			}
			puts("");
		}
		if(testcase)
			puts("");
	}
	return 0;
}
/*
2
"#$&/|[]+;:-." -1.2 1.2 0.1 -2 1 0.05
"1234567890AB" -1.2 -0.8 0.02 -0.5 0.5 0.02
*/
