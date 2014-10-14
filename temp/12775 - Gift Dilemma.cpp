#include <stdio.h> 
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
long long countSolution(long long n1, long long n2, long long n) {
	long long a, b, g;
    g = exgcd(n1, n2, a, b); // a*n1 + b*n2 = gcd(n1,2)
    if(n%g) return 0;
	long long k = n/g, k1, k2;
    a *= k, b *= k;// a*n1 + b*n2 = n
    // (a+F)*n1 + (b+G)*n2 = n =>  Fn1 + Gn2 = 0,
    //F = lcm(n1, n2)/n1 * i, G = lcm(n1, n2)/n2 * i
    k1 = n1*n2/g/n1, k2 = n1*n2/g/n2;
    if(a < 0) { // adjust a >= 0
        k = -(a/k1) + (a%k1 != 0);
        a += k*k1, b -= k*k2;
    }
    if(b < 0) { // adjust b >= 0
        k = -(b/k2) + (b%k2 != 0);
        a -= k*k1, b += k*k2;
    }
    if(a < 0 || b < 0) return 0;
    long long x1, x2, y1, y2;
    // minimize a, maximize b
    k = a/k1;
    a -= k*k1;
    b += k*k2;
    x1 = a, y1 = b;
    // maximize a, minimize b
    k = b/k2;
    a += k*k1;
    b -= k*k2;
    x2 = a, y2 = b;
    return (x2 - x1) / k1 + 1;
}
int main() {
	int testcase, cases = 0;
	long long A, B, C, P, ret, ta, tb;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%lld %lld %lld %lld", &A, &B, &C, &P);
		long long g = exgcd(exgcd(A, B, ta, tb), C, ta, tb);
		P /= g, A /= g, B /= g, C /= g;
		ret = 0;
		for (long long i = 0; P - C * i >= 0; i++)
			ret += countSolution(A, B, P - C * i);
		printf("Case %d: %lld\n", ++cases, ret);
	}
	return 0;
}
/*
1
202 203 200 606
*/
