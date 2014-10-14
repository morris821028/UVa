#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;

long long gcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y; 
	return y;
}
long long exgcd(long long x, long long y, long long &a, long long &b) {
    // ax + by = gcd(x,y)
    int flag = 0;
    long long t, la = 1, lb = 0, ra = 0, rb = 1;
    while(x%y) {
        if(flag == 0)
            la -= x/y*ra, lb -= x/y*rb;
        else
            ra -= x/y*la, rb -= x/y*lb;
        t = x, x = y, y = t%y;
        flag = 1 - flag;
    }
    if(flag == 0)
        a = ra, b = rb;
    else
        a = la, b = lb;
    return y;
}
long long countSolution(long long n1, long long n2, long long n, 
					long long lx, long long rx, long long ly, long long ry) {
//	printf("%lld %lld %lld\n", n1, n2, n);
	if (lx > rx || ly > ry)	return 0;
	if (n1 == 0)	return rx - lx + 1;
	if (n2 == 0)	return ry - ly + 1;
	long long a, b, g;
    g = exgcd(n1, n2, a, b); // a*n1 + b*n2 = gcd(n1,2)
    if(n%g) return 0;
	long long k = n/g, k1, k2;
    a *= k, b *= k;// a*n1 + b*n2 = n
    // (a+F)*n1 + (b+G)*n2 = n =>  Fn1 + Gn2 = 0, F = lcm(n1, n2)/n1 * i, G = lcm(n1, n2)/n2 * i
    k1 = n1*n2/g/n1, k2 = n1*n2/g/n2;
    long long x1, x2, x3, x4, y1, y2, y3, y4;
    k = (a - lx)/k1;
    a -= k*k1, b += k*k2;
    while (a < lx) {
    	if (k1 < 0)	a -= k1, b += k2;
    	else		a += k1, b -= k2;
    }
	x1 = a, y1 = b;
	
	k = (b - ly)/k2;
    a += k*k1, b -= k*k2;  
	while (b < ly) {
    	if (k2 < 0)	a += k1, b -= k2;
    	else		a -= k1, b += k2;
    }
	x3 = a, y3 = b;  
	
	k = (a - rx)/k1;
    a -= k*k1, b += k*k2;
    while (a > rx) {
    	if (k1 < 0)	a += k1, b -= k2;
    	else		a -= k1, b += k2;
    }
    x2 = a, y2 = b;
    
    k = (b - ry)/k2;
    a += k*k1, b -= k*k2;
	while (b > ry) {
    	if (k2 < 0)	a -= k1, b += k2;
    	else		a += k1, b -= k2;
    }
    x4 = a, y4 = b;
    long long l1 = 0, r1 = (x2 - x1)/ k1;
    long long l2 = (x3 - x1)/k1, r2 = (x4 - x1)/k1;
    if (l2 > r2)	swap(l2, r2);
    if (x1 > x2 || y3 > y4)	return 0;
//    printf("%lld %lld %lld %lld\n", x1, y1, x2, y2);
//    printf("%lld %lld %lld %lld\n", x3, y3, x4, y4);
//    printf("%lld %lld %lld %lld\n", l1, r1, l2, r2);
    l1 = max(l1, l2), r1 = min(r1, r2);
    if (l1 <= r1)	return r1 - l1 + 1;
    return 0;
}
long long read1Float() {
	long long x, y;
	scanf("%lld.%lld", &x, &y);
	return x * 10 + y;
}
int main() {    
//	freopen("in.txt","r+t",stdin);
//  freopen("out2.txt","w+t",stdout);
	int testcase, cases = 0;
	long long sx, sy, ex, ey;
	scanf("%d", &testcase);
	while (testcase--) {
		sx = read1Float();
		sy = read1Float();
		ex = read1Float();
		ey = read1Float();
		long long minx, miny, maxx, maxy;
		minx = ceil(min(sx, ex)/10.0);
		maxx = floor(max(sx, ex)/10.0);
		miny = ceil(min(sy, ey)/10.0);
		maxy = floor(max(sy, ey)/10.0);
		long long a, b, c;
		a = (ey - sy), b = (sx - ex), c = (a * sx + b * sy);
		a = a * 10, b = b * 10;
//		printf("[%lld %lld] [%lld %lld]\n", minx, maxx, miny, maxy);
		printf("%lld\n", countSolution(a, b, c, minx, maxx, miny, maxy));
	}
	return 0;
}
/*
5
10.1 10.1 11.2 11.2
10.2 100.3 300.3 11.1
1.0 1.0 2.0 2.0
1.0 1.0 1.0 1.0
1.0 3.0 1.0 7.0

100
74779.7 170072.4 114261.9 224.6
12284.7 149345.2 89292.2 24355.6
119238.0 59748.9 153776.5 88822.9
146984.2 79235.1 116519.4 144150.1
75703.5 8776.5 147012.5 132491.5
93698.8 27585.7 137374.4 134649.2

100
142566.2 47373.1 4487.9 81130.6
122932.1 117873.7 7944.5 24862.7
164852.3 50346.6 58670.9 47341.7
140828.3 21325.9 141292.5 16763.8
144206.3 130562.5 96260.1 53203.7

100
175593.7 137910.8 151744.6 21975.7
66918.0 141841.9 170688.8 108941.3
110334.9 103217.3 145166.0 126201.0
40233.7 62521.1 116634.3 146758.8
187820.7 131930.2 69771.4 66737.3
*/
