#include <stdio.h> 
#include <string.h>

// in AES, GF(2^8), m(x) = x^8 + x^4 + x^3 + x + 1
class GaloisField {
public:
	unsigned char v[32];
	int n;
	GaloisField() {
		n = 8;
		memset(v, 0, sizeof(v));
	}
	GaloisField(int val) {
		n = 8;
		memset(v, 0, sizeof(v));
		for (int i = 0; i < 8; i++)
			v[i] = (val>>i)&1;
	}
	GaloisField(const int a[], int an) {
		memset(v, 0, sizeof(v));
		n = 8;
		for (int i = 0; i <= an; i++)
			v[i] = a[i];
	}
	GaloisField operator+(const GaloisField &a) const {
		GaloisField r;
		for (int i = 0; i <= r.n; i++)
			r.v[i] = v[i] xor a.v[i];
		r.normal();
		return r;
	}
	GaloisField operator-(const GaloisField &a) const {
		return (*this) + a;
	}
	GaloisField operator*(const GaloisField &a) const {
		GaloisField r;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= a.n; j++) 
				r.v[i+j] = r.v[i+j] xor (v[i] and a.v[j]);
		r.normal();
		return r;
	}
	GaloisField shift(int sn) const {
		GaloisField r;
		for (int i = 0; i < n; i++)
			r.v[i + sn] = v[i];
		return r;
	}
	bool operator<(const GaloisField &a) const {
		for (int i = 16; i >= 0; i--) {
			if (v[i] == 1 && a.v[i] == 1)
				return true;
			if (v[i] == 1 && a.v[i] == 0)
				return false;
			if (v[i] == 0 && a.v[i] == 1)
				return false;
		}
		return false;
	}
	GaloisField operator/(const GaloisField &a) const {
		for (int i = 16; i >= 0; i--) {
			if (a.v[i] == 1 && v[i] == 0)
				return GaloisField();
			if (a.v[i] == 0 && v[i] == 1)
				break;
		}
		GaloisField r, b = (*this), c;
		
		for (int i = n; i >= 0; i--) {
			c = a.shift(i);
			if (c < b) {
				r.v[i] = 1;
				for (int j = 16; j >= 0; j--)
					b.v[j] = b.v[j] xor c.v[j];
			}
		}
		r.normal();
		return r;
	}
	GaloisField operator%(const GaloisField &a) const {
		GaloisField ret = (*this) - (*this) / a * a;
		return ret;
	}
	bool isZero() const {
		for (int i = 16; i >= 0; i--)
			if (v[i])	return 0;
		return 1;
	}
	GaloisField inverse() {
		const int m[] = {1, 1, 0, 1, 1, 0, 0, 0, 1}, mn = 8; // m(x) = x^8 + x^4 + x^3 + x + 1
		GaloisField y(m, mn);
		GaloisField g, a, b;
		
		exgcd((*this), y, g, a, b); // a x + b y = g
		return a;
	}
	void exgcd(GaloisField x, GaloisField y, GaloisField &g, GaloisField &a, GaloisField &b) {
		if (y.isZero()) {
			g = x, a = GaloisField(1), b = GaloisField(0);
		} else {
			exgcd(y, x%y, g, b, a), b = b - (x / y) * a;
		}
	}
	void normal() {
		const int m[] = {1, 1, 0, 1, 1, 0, 0, 0, 1}, mn = 8; // m(x) = x^8 + x^4 + x^3 + x + 1
		for (int i = 16; i - mn >= 0; i--) {
			if (v[i] == 1) {
				for (int j = mn, k = i; j >= 0; j--, k--)
					v[k] = v[k] xor (m[j]);
			}
		}
	}
	void print() const {
		for (int i = 7; i >= 0; i--) {
			printf("%d", v[i]);
			if (i%4 == 0)	printf(" ");
		}
		puts("");
	}
	int getHbits() const {
		return v[7]<<3 | v[6]<<2 | v[5]<<1 | v[4];
	}
	int getLbits() const {
		return v[3]<<3 | v[2]<<2 | v[1]<<1 | v[0];
	}
};

void testGF() {
	int va[] = {1, 1, 1, 0, 1, 1, 0, 0};
	int vb[] = {0, 1, 0, 0, 0, 0, 1, 0};
	for (int i = 0; i < 256; i++) {
		GaloisField a(i);
		GaloisField b = a.inverse();
		printf("%X%X ", b.getHbits(), b.getLbits());
		if (i%16 == 15) puts("");
	}
}

class GF_Polynominal {
public:
	GaloisField v[32];
	int n;
	GF_Polynominal() {
		n = 4;
		for (int i = 0; i < 16; i++)
			v[i] = GaloisField();
	}
	GF_Polynominal(const GaloisField a[], int an) {
		n = 4;
		for (int i = 0; i <= an; i++)
			v[i] = a[i];
	}
	GF_Polynominal operator+(const GF_Polynominal &a) const {
		GF_Polynominal r;
		for (int i = 0; i <= r.n; i++)
			r.v[i] = v[i] + a.v[i];
		r.normal();
		return r;
	}
	GF_Polynominal operator-(const GF_Polynominal &a) const {
		return (*this) + a;
	}
	GF_Polynominal operator*(const GF_Polynominal &a) const {
		GF_Polynominal r;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j <= a.n; j++) 
				r.v[i+j] = r.v[i+j] + (v[i] * a.v[j]);
		r.normal();
		return r;
	}
	GF_Polynominal shift(int sn) const {
		GF_Polynominal r;
		for (int i = 0; i < n; i++)
			r.v[i + sn] = v[i];
		return r;
	}
	bool operator<(const GF_Polynominal &a) const {
		for (int i = 8; i >= 0; i--) {
			if (!v[i].isZero() && !a.v[i].isZero())
				return true;
			if (v[i].isZero() != a.v[i].isZero())
				return false;
		}
		return false;
	}
	GF_Polynominal operator/(const GF_Polynominal &a) const {
		for (int i = 8; i >= 0; i--) {
			if (!a.v[i].isZero() && v[i].isZero())
				return GF_Polynominal();
			if (a.v[i].isZero() && !v[i].isZero())
				break;
		}
		GF_Polynominal r, b = (*this), c;
		
		for (int i = n; i >= 0; i--) {
			c = a.shift(i);
			if (c < b) {
				GaloisField t, x, y;
				for (int j = 16; j >= 0; j--) {
					if (!c.v[j].isZero()) {
						y = c.v[j], x = b.v[j];
						break;
					}
				}
				t = y.inverse() * x;
//				b.print();
//				c.print();
//				printf("gg %d\n", i);
//				y.print();
//				x.print();
//				y.inverse().print();
//				t.print();
				r.v[i] = t;
				for (int j = 8; j >= 0; j--)
					b.v[j] = b.v[j] - c.v[j] * t;
			}
		}
//		printf("---> mod "); b.print();
//		puts("");
//		puts("div begin");
//		print();
//		a.print();
//		r.print();
//		(r * a).print();
//		(r * a + b).print();
//		puts("div end\n");
		r.normal();
		return r;
	}
	GF_Polynominal operator%(const GF_Polynominal &a) const {
		GF_Polynominal ret = (*this) - (*this) / a * a;
		return ret;
	}
	bool isZero() {
		for (int i = 8; i >= 0; i--)
			if (!v[i].isZero())	return 0;
		return 1;
	}
	GF_Polynominal inverse() {
		const GaloisField m[] = {GaloisField(1), GaloisField(0), GaloisField(0), GaloisField(0), GaloisField(1)};
		const int mn = 4; // m(x) = x^4 + 1
		GF_Polynominal y(m, mn);
		GF_Polynominal g, a, b;
		
		exgcd((*this), y, g, a, b); // a x + b y = g
		
		return a / g;
	}
	void exgcd(GF_Polynominal x, GF_Polynominal y, GF_Polynominal &g, GF_Polynominal &a, GF_Polynominal &b) {
//		puts("exgcd -----------------");
//		x.print();
//		y.print();
//		getchar();
		if (y.isZero()) {
			const GaloisField m1[] = {GaloisField(1)};
			const GaloisField m0[] = {GaloisField(0)};
			g = x, a = GF_Polynominal(m1, 1), b = GF_Polynominal(m0, 1);
			// a = g.inverse();
		} else {
			exgcd(y, x%y, g, b, a), b = b - (x / y) * a;
		}
	}
	void normal() {
		const GaloisField m[] = {GaloisField(1), GaloisField(0), GaloisField(0), GaloisField(0), GaloisField(1)};
		const int mn = 4; // m(x) = x^4 + 1
		for (int i = 16; i - mn >= 0; i--) {
			if (!v[i].isZero()) {
				GaloisField t = v[i];
				for (int j = mn, k = i; j >= 0; j--, k--)
					v[k] = v[k] - (m[j] * t);
			}
		}
	}
	void print() const {
		for (int i = 3; i >= 0; i--) {
			printf("%X%X ", v[i].getHbits(), v[i].getLbits());
			printf("x^%d", i);
			if (i)	printf(" + ");
		}
		puts("");
	}
};

void testPoly() {
	const GaloisField m[] = {GaloisField(2), GaloisField(1), GaloisField(1), GaloisField(3)};
	const GaloisField m2[] = {GaloisField(14), GaloisField(9), GaloisField(13), GaloisField(11)};
	const int mn = 3, mn2 = 3;
	GF_Polynominal a(m, mn), b(m2, mn2);
	
	a.print();
	b.print();
	
	GF_Polynominal c = a * b;
	c.print();
	
	GF_Polynominal d = a.inverse();
	d.print();
}
int main() {
	testGF();
	testPoly();
	return 0;
}

