// thanks for flere help debug. 
#include <stdio.h> 
#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define eps 1e-6
struct Pt {
    int x, y;
    Pt(int a = 0, int b = 0):
    	x(a), y(b) {}
    bool operator<(const Pt &a) const {
        if(fabs(x-a.x) > eps)
            return x < a.x;
        return y < a.y;
    }
	Pt operator-(const Pt &a) const {
		Pt ret;
		ret.x = x - a.x;
		ret.y = y - a.y;
        return ret;
    }
};
double dist(Pt a, Pt b) {
	return hypot(a.x - b.x, a.y - b.y);
}
double length(Pt a) {
	return hypot(a.x, a.y);
}
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}

double distProjection(Pt as, Pt at, Pt s) {
	long long a, b, c;
	a = at.y - as.y;
	b = as.x - at.x;
	c = - (a * as.x + b * as.y);
	return fabs(a * s.x + b * s.y + c) / hypot(a, b);
}
void distProjection2(Pt as, Pt at, Pt s, long long &p, long long &q) {
	long long a, b, c;
	a = at.y - as.y;
	b = as.x - at.x;
	c = - (a * as.x + b * as.y);
	p = (a * s.x + b * s.y + c) * (a * s.x + b * s.y + c);
	q = a*a + b*b;
}
int main() {
	Pt p[4];
	while(true) {
		int end = 1;
		for(int i = 0; i < 4; i++) {
			scanf("%d %d", &p[i].x, &p[i].y);
			end &= p[i].x == 0 && p[i].y == 0;
		}
		if(end)	
			break;
		double h1 = distProjection(p[0], p[1], p[2]);
		double h2 = distProjection(p[1], p[2], p[3]);
		long long n, m;
		if(h1 <= h2)
			distProjection2(p[0], p[1], p[2], n, m);
		else
			distProjection2(p[1], p[2], p[3], n, m);
		long long g = __gcd(n, m);
		n /= g, m /= g;
		m *= 4;
		g = __gcd(n, m);
		n /= g, m /= g;
		if(min(h1, h2) < eps)
			while(1);
		printf("(%lld/%lld)*pi\n", n, m);
	}
	return 0;
}
/*
0 0 2 3 5 5 3 2
0 0 2 3 6 3 4 0
0 0 10 0 10 10 0 10
0 0 0 0 0 0 0 0
*/
