#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
double P[32], Q[32];
const double pi = acos(-1);
#define eps 1e-6
void integral(double Q[]) {
	for (int i = 31; i >= 1; i--)
		Q[i] = Q[i-1] / (i);
	Q[0] = 0;
}
double calcVal(double Q[], double x) {
	double ret = 0;
	for (int i = 31; i >= 0; i--)
		ret = ret * x + Q[i];
	return ret;
}
int main() {
	int testcase, cases = 0;
	int n, slices, stacks;
	double a, b;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		memset(P, 0, sizeof(P));
		memset(Q, 0, sizeof(Q));
		for (int i = n; i >= 0; i--)
			scanf("%lf", &P[i]);
			
		scanf("%lf %lf", &a, &b);
		scanf("%d %d", &slices, &stacks);
		
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= n; j++)
				Q[i+j] += P[i] * P[j];
		integral(Q);
		double trueVal = (calcVal(Q, b) - calcVal(Q, a)) * pi;
		double apprVal = 0;
		double dx = (b - a) / stacks, dtheta = 2 * pi / slices;
		for (double x = a; x + dx - eps <= b; x += dx) {
			double x1 = x, x2 = x + dx, x12;
			double fx1, fx2, S1, S2, fx12, S12;
			fx1 = calcVal(P, x1);
			fx2 = calcVal(P, x2);
			S1 = fx1 * fx1 * sin(dtheta) /2;
			S2 = fx2 * fx2 * sin(dtheta) /2;
			apprVal += dx * (S1 + S2 + sqrt(S1 * S2)) /3 * slices;
		}
		printf("Case %d: %.4lf\n", ++cases, fabs(trueVal - apprVal) * 100 / trueVal);
	}
	return 0;
}
/*
2
2 1 -4 5 1 4 4 3
1 1 0 1 4 4 3
*/
