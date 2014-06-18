#include <stdio.h>
#include <math.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while(testcase--) {
		double N, M, A, B, C;
		scanf("%lf %lf %lf %lf", &N, &M, &A, &B);
		
		C = (M * (A + B) - N * A) / B;
		
		printf("Case #%d: ", ++cases);
		if(C >= 0 && C <= 10)
			printf("%.2lf\n", C);
		else
			puts("Impossible");
	}
	return 0;
}
/*
3
7 8 1 1
7 9 5 2
9.05 9.20 28 20
*/
