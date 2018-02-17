#include <bits/stdc++.h>
using namespace std;
/*
https://en.wikipedia.org/wiki/Altitude_(triangle)
https://zh.wikipedia.org/wiki/%E6%97%81%E5%88%87%E5%9C%93
*/
struct Pt {
	double x, y;
	void read() {
		scanf("%lf %lf", &x, &y);
	}
	int isZero() {
		return fabs(x) < 1e-6 && fabs(y) < 1e-6;
	}
	double dist(const Pt &p) const {
		return sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
	}
};
int main() {
	int cases = 0;
	Pt p[3];
	while (1) {
		p[0].read(), p[1].read(), p[2].read();
		if (p[0].isZero() && p[1].isZero() && p[2].isZero())
			break;
		double a, b, c;
		a = p[1].dist(p[2]);
		b = p[0].dist(p[2]);
		c = p[0].dist(p[1]);
		double jax, jay, jbx, jby, jcx, jcy;
		jax = (-a*p[0].x+b*p[1].x+c*p[2].x)/(-a+b+c);
		jay = (-a*p[0].y+b*p[1].y+c*p[2].y)/(-a+b+c);
		jbx = (a*p[0].x-b*p[1].x+c*p[2].x)/(a-b+c);
		jby = (a*p[0].y-b*p[1].y+c*p[2].y)/(a-b+c);
		jcx = (a*p[0].x+b*p[1].x-c*p[2].x)/(a+b-c);
		jcy = (a*p[0].y+b*p[1].y-c*p[2].y)/(a+b-c);
		printf("Case %d:\n", ++cases);
		printf("%.3lf %.3lf\n%.3lf %.3lf\n%.3lf %.3lf\n", jax, jay, jbx, jby, jcx, jcy);
	}
	return 0;
}
