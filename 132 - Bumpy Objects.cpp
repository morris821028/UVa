#include <stdio.h> 
#include <math.h>
#include <string.h>
#include <algorithm>
using namespace std;
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
	Pt operator-(const Pt &a) const {
		Pt ret;
		ret.x = x - a.x;
		ret.y = y - a.y;
        return ret;
    }
};
double dot(Pt a, Pt b) {
	return a.x * b.x + a.y * b.y;
}
double cross2(Pt a, Pt b) {
	return a.x * b.y - a.y * b.x;
}
double cross(Pt o, Pt a, Pt b) {
    return (a.x-o.x)*(b.y-o.y)-(a.y-o.y)*(b.x-o.x);
}
int between(Pt a, Pt b, Pt c) {
	return dot(c - a, b - a) >= 0 && dot(c - b, a - b) >= 0;
}
int onSeg(Pt a, Pt b, Pt c) {
	return between(a, b, c) && fabs(cross(a, b, c)) < eps;
}
int monotone(int n, Pt p[], Pt ch[]) {
    sort(p, p+n);
    int i, m = 0, t;
    for(i = 0; i < n; i++) {
        while(m >= 2 && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    for(i = n-1, t = m+1; i >= 0; i--) {
        while(m >= t && cross(ch[m-2], ch[m-1], p[i]) <= 0)
            m--;
        ch[m++] = p[i];
    }
    return m - 1;
}
int main() {
	char testcase[105];
	Pt P[1024], CH[1024], IN[1024];
	while(scanf("%s", testcase) == 1) {
		if(!strcmp(testcase, "#"))
			break;
		double 	x, y;
		int 	n = 0, m;
		Pt mc;
		scanf("%lf %lf", &mc.x, &mc.y);
		while(scanf("%lf %lf", &x, &y) == 2) {
			if(x == 0 && y == 0)
				break;
			IN[n] = P[n] = Pt(x, y);
			n++;
		}
		m = monotone(n, P, CH);
		int ret = 0x3f3f3f3f;
		for(int i = 0, j = m - 1; i < m; j = i++) {
			if(between(CH[i], CH[j], mc)) {
				int mn = 0;
				for(int k = 0; k < n; k++)
					if(onSeg(CH[i], CH[j], IN[k]))
						mn = max(mn, k);
				ret = min(ret, mn);
			}
		}
		printf("%-20s%d\n", testcase, ret + 1);
	}
	return 0;
}
/*
Object2
4 3
3 2  5 2  6 1  7 1  6 3  4 7  1 1  2 1  0 0
Square 
2 2
1 1  3 1  3 3  1 3  0 0
#
*/
