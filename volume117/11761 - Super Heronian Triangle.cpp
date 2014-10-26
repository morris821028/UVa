#include <stdio.h>
#include <math.h>
#include <algorithm>
using namespace std;

// a * b * c = 4 * R * A
#define MAXS 40001
long long gcd(long long x, long long y) {
	long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
int intArea(long long a, long long b, long long c) {
	if (a >= b + c || b >= a + c || c >= a + b)
		return 0;
	long long A = a + b + c, B = 2, g;
	g = gcd(A, B), A /= g, B /= g;
	A = A * (b + c - a), B = B * 2;
	g = gcd(A, B), A /= g, B /= g;
	A = A * (a + c - b), B = B * 2;
	g = gcd(A, B), A /= g, B /= g;
	A = A * (a + b - c), B = B * 2;
	g = gcd(A, B), A /= g, B /= g;
	if (A % B)	return 0;
	A = A / B;
	long long sq = sqrt(A);
	if (sq * sq != A)	return 0;
	return sq;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out2.txt", "w+t", stdout); 
	long long R, A;
	while (scanf("%lld %lld", &R, &A) == 2 && R + A) {
		long long N = 4 * R * A, c;
		long long ra, rb, rc;
		ra = rb = rc = -1;
		
		for (long long a = 1; a < MAXS; a++) {
			if (N%a)	continue;
			for (long long b = max(a, N / a / MAXS); a * b * b <= N && b < MAXS; b++) {
				c = N / a / b;
				if (c >= MAXS)	continue;
				if (a * b * c != N || a+b <= c || intArea(a, b, c) != A)	continue;
				ra = a, rb = b, rc = c;
				a = MAXS, b = MAXS; // break;
			}
		}
		printf("%lld %lld %lld\n", ra, rb, rc);
	}
	return 0;
}
/*
500000 700000000
22620 1071
*/
