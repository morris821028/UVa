#include <stdio.h> 
#include <string.h>
#include <math.h>
using namespace std;
#define eps 1e-6
int main() {
	double A[16][64], B[16][64];
	for (int M = 0; M <= 9; M++) {
		for (int E = 1; E <= 30; E++) {
			// maxval = (1 - 2^{-M - 1}) \times 2^{2^{E} - 1}
			// log10(maxval) = log10(a) + b, 0 < a < 10, b \in N
			double p = 1 - pow(2, -M - 1);
			double q = pow(2, E) - 1;
			double logsum = log10(p) + log10(2) * q;
			double b = floor(logsum);
			double a = pow(10, logsum - b);
			A[M][E] = a, B[M][E] = b;
		}
	}
	char s[128];
	while (scanf("%s", s) == 1) {
		if (!strcmp(s, "0e0"))
			break;
		for (int i = 0; s[i]; i++)
			if (s[i] == 'e')	s[i] = ' ';
		double p, q;
		sscanf(s, "%lf %lf", &p, &q);
		for (int i = 0; i <= 9; i++)
			for (int j = 1; j <= 30; j++)
				if (fabs(A[i][j] - p) < eps && fabs(B[i][j] - q) < eps)
					printf("%d %d\n", i, j);
	}
	return 0;
}
/*
5.699141892149156e76
9.205357638345294e18
0e0
*/
