#include <bits/stdc++.h>
using namespace std;
const long double PI = acos(-1), e = exp(1);
const int MAXN = 1001;
double f[MAXN];
double stirling(int n) {
	if (n < MAXN)
		return f[n];
	return log2(sqrt(2*PI*n)) + n*log2(n/e);
}
double logC(int n, int m) {
	return stirling(n) - stirling(n - m) - stirling(m);
}

class SimpsonIntegral {
public:
	const double eps = 1e-6;
	const double pi = acos(-1);
	const double sqr2pi = sqrt(2 * pi);
	double mu, sigma; // function coefficient
	double f(double x) { // usually replace
		return exp(-(pow(x - mu, 2)/2.0/sigma/sigma))/ sigma / sqr2pi;
	}
	void setCoefficient(double m, double s) {
		this->mu = m, this->sigma = s;
	} 
	double simpson(double a, double b, double fa, double fb, double fab) {
		return (fa + 4 * fab + fb) * (b - a) / 6.0;
	}
	double integral(double l, double r) {
		return integral(l, r, eps);
	}
private:
	double integral(double a, double b, double c, double eps, double A, double fa, double fb, double fc) {
		double ab = (a + b)/2, bc = (b + c)/2;
		double fab = f(ab), fbc = f(bc);
		double L = simpson(a, b, fa, fb, fab), R = simpson(b, c, fb, fc, fbc);
		if (fabs(L + R - A) <= 15 * eps)
			return L + R + (L + R - A) / 15.0;
		return integral(a, ab, b, eps/2, L, fa, fab, fb) + integral(b, bc, c, eps/2, R, fb, fbc, fc);
	}
	double integral(double a, double b, double eps) {
		double ab = (a + b) /2;
		double fa = f(a), fb = f(b), fab = f(ab);
		return integral(a, ab, b, eps, simpson(a, b, fa, fb, fab), fa, fab, fb);
	}
} tool;

double binom(double n, double a, double b) {
    double a1, b1;
    double d = sqrt(n/2.0);
    a1 = 0.5 * (1.0 + erf((a - n/2.0 - 0.5) / d));
    b1 = 0.5 * (1.0 + erf((b - n/2.0 + 0.5) / d));
    return b1 - a1;
}
int main() {
	f[0] = 0;
	for (int i = 1; i < MAXN; i++)
		f[i] = log2(i) + f[i-1];
	int n, a, b;
	int cases = 0;
	while (scanf("%d %d %d", &n, &a, &b) == 3) {
		cases++;
		if (n < MAXN) {
			double ret = 0;
			for (int i = a; i <= b; i++)
				ret += pow(2, logC(n, i) - log2(2) * n);
			printf("%.4lf\n", ret);
		} else {
//			tool.setCoefficient(n/2.0, sqrt(n/4.0));
//			double ret = 0, l = a - 0.5, r = b + 0.5;
//			if (r < n/2.0 || l > n/2.0)
//				ret = tool.integral(l, r);
//			else
//				ret = tool.integral(l, n/2.0) + tool.integral(n/2.0, r);
//			printf("%.4lf\n", ret);
			printf("%.4lf\n", binom(n, a, b));
		} 
	}
    return 0;
} 

