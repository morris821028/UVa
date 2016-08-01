#include <stdio.h>
#include <math.h>
#include <algorithm>
#include <assert.h>
using namespace std;

double a, b, c, d, L;
/*
	B cos theta - A cos theta = d - b
	B sin theta + A sin theta = c - a
	A + B = L
 */ 
int main() {
    while (scanf("%lf %lf %lf %lf %lf", &a, &b, &c, &d, &L) == 5) {
        if (a > c) {
            swap(a, c);
            swap(b, d);
        }
        L = max(L, hypot(a - c, b - d));
        if (b == d && fabs(c - a - L) < 1e-8) {
        	printf("%.10lf %.10lf\n", a, b);
        	continue;
        }
        double v1 = d - b, v2 = c - a;
        double cos = v2 / L;
        double sin = sqrt(1 - cos * cos);
        double A, B;
        B = (v1 / sin + L)/2;
        A = L - B;
        printf("%.10lf %.10lf\n", a + cos * A, b - sin * A);
    }
    return 0;
}
/*
 2 5 7 4 5.099
 2 5 7 4 10
 10 20 30 40 31
 2 5 2 7 10
 2 7 2 5 10
 2 10 3 10 10
 2 5 2 7 2
 2 7 2 5 2
 2 5 2 5 0
 2 5 2 5 1
 2 5 3 5 1
*/
