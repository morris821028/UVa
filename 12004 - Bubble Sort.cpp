#include <stdio.h>
typedef long long Int64;
struct frac {
	Int64 num, den;
	void print() {
		simpler();
		if(den != 1)
			printf("%lld/%lld\n", num, den);
		else
			printf("%lld\n", num);;
	}
	void simpler() {
		Int64 g = gcd(num, den);
		num /= g;
		den /= g;
	}
	Int64 gcd(Int64 x, Int64 y) {
		if(x == 0)	return y;
		if(y == 0)	return x;
		Int64 tmp;
		while(x%y) {
			tmp = x, x = y, y = tmp%y;
		}
		return y;
	}
};
int main() {
	int t, Case = 0;
	Int64 n;
	scanf("%d", &t);
	while(t--) {
		scanf("%lld", &n);
		printf("Case %d: ", ++Case);
		frac f = {n*(n-1), 4};
		f.print();
	}
    return 0;
}
