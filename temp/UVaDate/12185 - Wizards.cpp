// polynomial root test, find find n distinct roots. 
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;

const int MAXN = 512;
const double eps = 1e-10;
class Polynominal {
public:
	double v[MAXN];
	int n;
	Polynominal(int a = 0): n(a) {
		memset(v, 0, sizeof(v));
	}
	Polynominal(const double v[], int a = 0) {
		memset(this->v, 0, sizeof(this->v)), n = a;
		for (int i = 0; i <= n; i++)
			this->v[i] = v[i];
	}
	Polynominal operator+(const Polynominal &a) const {
		Polynominal r(max(n, a.n));
		for (int i = 0; i <= r.n; i++)
			r.v[i] = v[i] + a.v[i];
		r.normal();
		return r;
	}
	Polynominal operator-(const Polynominal &a) const {
		Polynominal r(max(n, a.n));
		for (int i = 0; i <= r.n; i++)
			r.v[i] = v[i] - a.v[i];
		r.normal();
		return r;
	}
	Polynominal operator*(const Polynominal &a) const {
		Polynominal r(n + a.n);
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= a.n; j++) 
				r.v[i+j] += v[i] * a.v[j];
		r.normal();
		return r;
	}
	Polynominal operator/(const Polynominal &a) const {
		if (n < a.n)	return Polynominal(0);
		Polynominal r(n - a.n);
		for (int i = 0; i <= r.n; i++)
			r.v[i] = v[i + a.n];
		for (int i = r.n; i >= 0; i--) {
			r.v[i] /= a.v[a.n];
			for (int j = i-1, k = a.n - 1; k >= 0 && j >= 0; j--, k--)
				r.v[j] -= r.v[i] * a.v[k];
		} 
//		r.normal(); // WTF, why I can't do this ? because mod use / a * a, larger eps. 
		return r;
	}
	Polynominal operator%(const Polynominal &a) const {
		Polynominal r = *this - (*this / a) * a;
		r.normal();
		return r;
	}
	Polynominal derivative() const {
		Polynominal r(n-1);
		for (int i = n-1; i >= 0; i--)
			r.v[i] = v[i+1] * (i+1);
		r.normal();
		return r;
	}
	Polynominal integral() const {
		Polynominal r(n+1);
		for (int i = n+1; i >= 1; i--)
			r.v[i] = v[i-1] / i;
		r.normal();
		return r;
	}
	void normal() {
		while (n >= 1 && !cmpZero(v[n]))	n--;
	}   
	bool isZero() {
		return n == 0 && !cmpZero(v[0]);
	}
	void print() {
        for (int i = n; i >= 0; i--) {
            printf("%.3lf", v[i], i);
            if (i != 0) printf(" x");
            if (i != 1 && i != 0) printf(" ^ %d", i);
            if (i != 0) printf(" + ");
            else printf("\n");
        }
    }
    static Polynominal gcd(Polynominal a, Polynominal b);
private:
	int cmpZero(double x) {
		if (fabs(x) < eps)	return 0;
		return x < 0 ? -1 : 1; 
	}
};
Polynominal Polynominal::gcd(Polynominal a, Polynominal b) {
//	a.print();
//	b.print();
//	getchar();
	if (b.isZero())	return a;
	else			return gcd(b, a % b);
}
void testPolynominal() {
	double va[] = {1, 2, 1};
	double vb[] = {2, 2};
	Polynominal a(va, 2), b(vb, 1);
	a.print();
	b.print();
	(a + b).print();
	(a / b).print();
	(a % b).print();
	(b % a).print();
}
int main() {
//	testPolynominal();
	int testcase, n;
	double v[MAXN];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);

		for (int i = n; i >= 0; i--)
			scanf("%lf", &v[i]);
			
		if (n == 0) {
			puts("Yes!");
			continue;
		}
		Polynominal f(v, n);
		Polynominal g = f.derivative();
		
		Polynominal t = Polynominal::gcd(f, g);
		puts(t.n == 0 ? "Yes!" : "No!");
	} 
	return 0;
}
/*
f(x) = (x - r)^n g(x)
f'(x) = n (x - r)^(n-1) g(x) + (x - r)^(n-1) g'(x)
gcd(f(x), f'(x)) = (x - r)^(n-1) h(x)
*/
/*
5
2 1 1 1
2 1 2 1
4 1 2 1 2 1
4 1 2 2 2 1
4 1 0 2 0 1 

10
10 9 1 0 17 23 25 12 21 19 11 2
3 -16 16 32 0
1 -32 16

*/
