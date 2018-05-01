#include <bits/stdc++.h> 
using namespace std;

double intA2(double c, double l, double r) {
	return 1.0/3*(r*r*r-l*l*l)-c*(r*r-l*l)+c*c*(r-l);
}
double intA1(double p[], int n, double c, double d, double l, double r) {
	double q[64] = {}, o[64] = {};
	for (int i = 0; i <= n; i++)
		q[i] = p[i];
	q[0] -= d;
	for (int i = 0; i <= n; i++)
		q[i] = q[i]*2;
	for (int i = 0; i <= n; i++)
		o[i+1] += q[i] - c*q[i+1];
	o[0] += -c*q[0];
	for (int i = n+2; i >= 1; i--)
		o[i] = o[i-1]/i;
	double v1 = 0, v2 = 0;
	for (int i = n+2; i >= 0; i--)
		v1 = v1*l + o[i], v2 = v2*r + o[i];
	return -(v2 - v1);
}
double intA0(double p[], int n, double d, double l, double r) {
	double q[64] = {}, o[64] = {};
	for (int i = 0; i <= n; i++)
		q[i] = p[i];
	q[0] -= d;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			o[i+j] += q[i]*q[j];
	}
	double v1 = 0, v2 = 0;
	for (int i = 2*n+1; i >= 1; i--)
		o[i] = o[i-1]/i;
//	for (int i = 2*n+1; i >= 0; i--)
//		printf("%lf ", o[i]);
//	puts("");
	for (int i = 2*n+1; i >= 0; i--) 
		v1 = v1*l + o[i], v2 = v2*r + o[i];
	return (v2 - v1);
}

double integral(double p[], int n, double l, double r) {
	double q[64] = {}, o[64] = {};
	for (int i = 0; i <= n; i++)
		q[i] = p[i];
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= n; j++)
			o[i+j] += q[i]*q[j];
	}
	double v1 = 0, v2 = 0;
	for (int i = 2*n+1; i >= 1; i--)
		o[i] = o[i-1]/i;
	for (int i = 2*n+1; i >= 0; i--) {
		printf("%lf ", o[i]);
		v1 = v1*l + o[i], v2 = v2*r + o[i];
	}
	puts("");
	puts("-------");
	return (v2 - v1);
}

double v_left, v_right;
double a_left, a_right;
double b_left, b_right;
double evalQuadPoly(double p[], int n, double c, double d) {
	// y = ax + b, (c, d) => b = d - ac
	// => integral (p(x) - ax - d + ac)^2 dx
	// => integral (p(x)-d - (x-c)a)^2 dx
	// => integral (x-c)^2 a^2 - 2(x-c)(p(x)-d) a + (p(x)-d)^2 dx
	// => integral (x-c)^2 a^2 - 2(x-c)(p(x)-d) a + (p(x)-d)^2 dx
	// => min \int{-1}^{c} Q dx + min \int{c}^{1} Q dx
	double ta, tb, tc;
	ta = intA2(c, -1, c);
	tb = intA1(p, n, c, d, -1, c);
	tc = intA0(p, n, d, -1, c);
	a_left = -tb/2/ta;
	v_left = tc-tb*tb/4/ta;
	b_left = d-a_left*c;
	ta = intA2(c, c, 1);
	tb = intA1(p, n, c, d, c, 1);
	tc = intA0(p, n, d, c, 1);
	a_right = -tb/2/ta;
	v_right = tc-tb*tb/4/ta;
	b_right = d-a_right*c;
//	printf("%lf %lf %lf %lf\n", a_left, b_left, a_right, b_right);
//	printf("%lf %lf %lf\n", v_left + v_right, v_left, v_right);
	return v_left + v_right;
}

int main() {
	int n, cases = 0;
	double p[16], c;
	while (scanf("%d", &n) == 1 && n) {
		for (int i = n; i >= 0; i--)
			scanf("%lf", &p[i]);
		scanf("%lf", &c);
//		double d = -0.367;
//		double d = -0.39;
//		for (double d = -0.5; d <= 0.3; d += 0.05)
//			evalQuadPoly(p, n, c, d);
		double l = -11, r = 11, mid, midmid, md, mmd;
        for (int it = 0; it < 100; it++) {
            mid = (l+r)/2;
            midmid = (mid+r)/2;
            md = evalQuadPoly(p, n, c, mid);
            mmd = evalQuadPoly(p, n, c, midmid);
            if (md > mmd)
                l = mid;
            else
                r = midmid;
        }
        printf("Case %d: %.3lf %.3lf %.3lf %.3lf\n", ++cases, a_left, b_left, a_right, b_right);
	}
	return 0;
}
/*

*/
