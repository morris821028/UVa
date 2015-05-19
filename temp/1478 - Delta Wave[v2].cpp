#include <stdio.h> 
#include <string.h>
#include <algorithm>
using namespace std;

// Catalan number, Math
// Catalan number f(n) = f(n-1) * (4n-2) / (n+1), f(n) = C(2n, n) / (n+1)
// ----> this problem
// g(n) = \sum_{i = 1}^{n/2} \binom{n}{2 i} f(i)
// assume a(i) = \binom{n}{2 i} f(i)
//	   => a(i) = a(i-1) \times \frac{(n-2i+1)(n-2i+2)}{i(i+1)} 
const int MAXD = 600;
/*
	Simple version
*/
class BigInteger {
public:
	long long a[MAXD + 10];
	long long c;
	int len;
	BigInteger(long long v) {
		c = 100000000, len = 4;
		memset(a, 0, sizeof(a));
		a[0] = v, normal();
	}
	BigInteger operator+(BigInteger &x) const {
		BigInteger r(0);
		int vlen = max(len, x.len) + 1;
		for (int i = 0; i < vlen; i++)
			r.a[i] = a[i] + x.a[i];
		r.len = vlen, r.normal();
		return r;
	}
	BigInteger operator*(long long int &x) const {
		BigInteger r(0);
		for (int i = 0; i < len; i++)
			r.a[i] = a[i] * x;
		r.len = len + 1, r.normal();
		return r;
	}
	BigInteger operator/(long long &x) const {
		BigInteger r(0);
		long long v = 0;
		for (int i = len; i >= 0; i--) {
			v = v * c + a[i];
			r.a[i] = v / x;
			v = v % x;
		}
		r.len = len, r.normal();
		return r;
	}
	void normal() {
		for (int i = 0; i <= len; i++) {
			if (a[i] >= c)
				a[i+1] += a[i] / c, a[i] %= c;
		}
		len = len + 1;
		while (len > 0 && a[len] == 0)	
			len--;
		len ++;
	}
	void print() {
		int st = 15;
		while (st > 0 && a[st] == 0)
			st--;
		char buf[512];
		char *p = buf;
		sprintf(p, "%lld", a[st]), st--;
		while (*p)	p++;
		while (st >= 0) {
			sprintf(p, "%08lld", a[st]), st--;
			while (*p)	p++;
		}
		
		int n = (int) (p - buf), f = 0;
		for (int i = n - 100; i < n; i++) {
			if (i < 0)	continue;
			if (buf[i] != '0' || i == n-1) {
				puts(buf + i);
				break;
			}
		}
	}
};
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		BigInteger a(1), r(1);
		for (int i = 1; i <= n/2; i++) {
			long long p = (long long) (n - 2 * i + 1) * (n - 2 * i + 2);
			long long q = (long long) i * (i+1);
			a = a * p;
			a = a / q;
			r = r + a;
		}
		r.print();
	}
	return 0;
}
