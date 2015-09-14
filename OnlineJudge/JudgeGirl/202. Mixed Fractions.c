#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int a, b, c;
} Frac;
int read(Frac *f) {
	int x, y, z;
	int r = scanf("%d %d %d", &x, &y, &z) == 3;
	f->a = x, f->b = y, f->c = z;
	return r;
}
int gcd(int x, int y) {
	int t;
	while (x%y)
		t = x, x = y, y = t%y;
	return y;
}
void add(Frac x, Frac y) {
	int a1 = x.a*x.c + (x.a < 0 ? -x.b : x.b), b1 = x.c;
	int a2 = y.a*y.c + (y.a < 0 ? -y.b : y.b), b2 = y.c;
	int a3 = a1*b2 + a2*b1, b3 = b1*b2;
	int g = gcd(a3, b3);
	a3 /= g, b3 /= g;
	printf("%d\n%d\n%d\n", a3/b3, abs(a3)%b3, b3);
}
void sub(Frac x, Frac y) {
	int a1 = x.a*x.c + (x.a < 0 ? -x.b : x.b), b1 = x.c;
	int a2 = y.a*y.c + (y.a < 0 ? -y.b : y.b), b2 = y.c;
	int a3 = a1*b2 - a2*b1, b3 = b1*b2;
	int g = gcd(a3, b3);
	a3 /= g, b3 /= g;
	printf("%d\n%d\n%d\n", a3/b3, abs(a3)%b3, b3);
}
void mul(Frac x, Frac y) {
	int a1 = x.a*x.c + (x.a < 0 ? -x.b : x.b), b1 = x.c;
	int a2 = y.a*y.c + (y.a < 0 ? -y.b : y.b), b2 = y.c;
	int a3 = a1*a2, b3 = b1*b2;
	int g = abs(gcd(a3, b3));
	a3 /= g, b3 /= g;
	if (b3 < 0)	a3 = -a3, b3 = -b3;
	printf("%d\n%d\n%d\n", a3/b3, abs(a3)%b3, b3);
}
void _div(Frac x, Frac y) {
	int a1 = x.a*x.c + (x.a < 0 ? -x.b : x.b), b1 = x.c;
	int a2 = y.a*y.c + (y.a < 0 ? -y.b : y.b), b2 = y.c;
	int a3 = a1*b2, b3 = b1*a2;
	int g = abs(gcd(a3, b3));
	a3 /= g, b3 /= g;
	if (b3 < 0)	a3 = -a3, b3 = -b3;
	printf("%d\n%d\n%d\n", a3/b3, abs(a3)%b3, b3);
}
int main() {
	Frac x, y;
	int op;
	while (read(&x) == 1) {
		scanf("%d", &op);
		read(&y);
		switch (op) {
			case 0: add(x, y); break;
			case 1: sub(x, y); break;
			case 2: mul(x, y); break;
			case 3: _div(x, y); break;
		}
	}
	return 0;	
}

