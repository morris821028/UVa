#include <stdio.h>
#include <math.h>
#define eps 1e-6
struct Pt {
    double x, y;
    Pt(double a = 0, double b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)
            return x < a.x;
        return y < a.y;
    }
    Pt operator+(const Pt &a) const {
        return Pt(x + a.x, y + a.y);
    }
	Pt operator-(const Pt &a) const {
        return Pt(x - a.x, y - a.y);
    }
    Pt operator/(const double a) const {
        return Pt(x/a, y/a);
    }
    int read() {
    	return scanf("%lf %lf", &x, &y);
    }
};
int main() {
	Pt A, B;
	const double pi = acos(-1); 
	int n;
	while(true) {
		A.read(), B.read(), scanf("%d", &n);
		if(n == 0)	break;
		double r, dist = hypot(A.x - B.x, A.y - B.y);
		if(n%2 == 0) {
			r = dist /2;
		} else {
			int m = (n - 1)/2;
			r = dist /2 / sin((double)m/2.0/n * 2 * pi);
		}
		printf("%lf\n", r * r * sin(2 * pi/n) * n/2);
	}
	return 0;
}
/*
0 0 3 0 3
*/
