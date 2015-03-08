#include <stdio.h> 
#include <math.h>
using namespace std;

class SimpsonIntegral {
public:
	const double eps = 1e-6;
	double a; // function coefficient
	double f(double x) { // usually replace
		return sqrt(1 + 4 * a * a * x * x);
	}
	void setCoefficient(double a) {
		this->a = a;
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
// integral parabola length
// \int \sqrt_{dx^{2} + dy^{2}} = \int \sqrt_{1 + dy^{2}/dx^{2}} dx
// = \int \sqrt_{1 + f'(x)^{2}} dx
int main() {
	int testcase, cases = 0;
	double D, H, B, L;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lf %lf %lf %lf", &D, &H, &B, &L);
		int n = ceil(B / D);
		double w = B / n, plen = L / n; // for a parabola
		double l = 0, r = H, len, mid;
		for (int it = 0; it < 100; it++) {
			mid = (l + r)/2; // parabola y = ax^2, pass (w/2, mid)
			tool.setCoefficient(4 * mid / w / w);
			len = 2 * tool.integral(0, w/2);
			if (len < plen)
				l = mid;
			else
				r = mid;
		}
		if (cases)	puts("");
		printf("Case %d:\n", ++cases);
		printf("%.2lf\n", H - l);
	}
	return 0;
}
