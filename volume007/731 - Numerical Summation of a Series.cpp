#include <bits/stdc++.h>
using namespace std;

double ret[3005];
int main() {
	for (int i = 0; i <= 300; i++) {
		double x = i;
		double sum = 0;
		if (i == 1) {
			ret[i*10] = 1;
			continue;
		}
		if (i) {
			const double eps = 1e-12;
			const double y = 1;
			double k = 1;
			// compute sum = phi(1) - phi(x)
			for (k = 1; k < 100000000; k++) {
				double s = (x-y)/(k*(k+x)*(k+y));
				if (s < eps)
					break;
				sum += s;
			}
			// phi(x) = phi(1) - sum + error
			double e;
			if (y >= 1) e = (log(k+x) - log(k))/x - (log(k+y) - log(k))/(y);
			else		e = (log(k+x) - log(k))/x - 1/k;
			sum = ret[(int) y*10] - sum + e;
		} else {
			double k;
			for (k = 1; k < 100000000; k++) {
				double s = 1/(k*k);
				if (s < 1e-12)
					break;
				sum += s;
			}
			sum += 1/k;
		}
		ret[i*10] = sum;
	}
	for (int i = 0; i <= 3000; i++) {
		if (i%10 == 0)
			continue;
		double x = (double) i/10;
		double y = floor(x);
		double sum = 0;
		double k;
		for (k = 1; k < 100000000; k++) {
			double s = (x-y)/(k*(k+x)*(k+y));
			if (fabs(s) < 1e-12)
				break;
			sum += s;
		}
		double e;
		if (y >= 1) e = (log(k+x) - log(k))/x - (log(k+y) - log(k))/(y);
		else		e = (log(k+x) - log(k))/x - 1/k;
		ret[i] = ret[(int)y*10] - sum + e;
	}
	for (int i = 0; i <= 3000; i++) {
		double x = (double) i/10;
		printf("%6.2f%17.12lf\n", x, ret[i]);
	}
	return 0;
}
