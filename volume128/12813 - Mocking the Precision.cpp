#include <stdio.h> 
#include <assert.h>

unsigned long long gcd(unsigned long long x, unsigned long long y) {
	unsigned long long t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
unsigned long long mpow(unsigned long long x, unsigned long long y) {
	unsigned long long r = 1;
	while (y) {
		if (y&1)	r = r * x;
		x = x * x, y >>= 1;
	}
	return r;
}
int main() {
	char s[1024];
	while (gets(s)) {
		int sign = 1, flag = 0, tail = 0;
		int cycle = 0;
		unsigned long long num = 0, cnum = 0, head = 0;
		int test = 0;
		for (int i = 0; s[i]; i++) {
			if (s[i] == '-') {
				sign = -1;
			} else if (s[i] == '.') {
				flag = 1;
			} else if (s[i] == '(') {
				for (i++; s[i] != ')'; i++)
					cnum = cnum * 10 + s[i] - '0', cycle++;
			} else {
				if (flag == 1)	tail++;
				if (flag == 1)
					num = num * 10 + s[i] - '0';
				else
					head = head * 10 + s[i] - '0';
				test++;
			}
		}
		assert(tail <= 8 && cycle <= 8 && cycle + tail <= 18);
		unsigned long long a, b, g;
		if (cycle)
			a = num * mpow(10, cycle) + cnum - num, b = mpow(10, cycle) - 1;
		else
			a = num , b = 1;
		g = gcd(a, b), a /= g, b /= g;
		b = b * mpow(10, tail);
		g = gcd(a, b), a /= g, b /= g;
		int f = 0;
		head += a/b;
		if (sign == -1)	printf("-");
		if (head)	printf("%llu", head), f = 1;
		if (a%b)	printf("%s%llu/%llu", f ? " " : "", a%b, b), f = 1;
		if (!f)		printf("0");
		puts("");
	}
	return 0;
}
/*
1.5
10
0.(3)
0.(142857)
0.1(23)
-0.(428571)
0.0(142857)
0.(9)
1.(9)
*/
