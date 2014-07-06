#include <stdio.h> 
#include <algorithm>
#include <set>
#include <math.h>
using namespace std;
#define eps 1e-3
struct Fraction {
	long long a, b;
	Fraction(long long x=0, long long y=1) {
		long long g = __gcd(x, y);
		a = x / g;
		b = y / g;
		if(b < 0)	a = -a, b = -b;
	}
	Fraction operator+(const Fraction &x) const {
		return Fraction(a * x.b + x.a * b, b * x.b);
	}
	Fraction operator-(const Fraction &x) const {
		return Fraction(a * x.b - x.a * b, b * x.b);
	}
	Fraction operator*(const Fraction &x) const {
		return Fraction(a * x.a, b * x.b);
	}
	Fraction operator/(const Fraction &x) const {
		return Fraction(a * x.b, b * x.a);
	}
	bool operator<(const Fraction &x) const {
		return a * x.b < b * x.a;
	}
};
int main() {
	int n, cases = 0, A[10];
	while(scanf("%d", &n) == 1 && n) {
		for(int i = 0; i < n; i++)
			scanf("%d", &A[i]);

		set<Fraction> ret;
		sort(A, A+n);
		do {
			set<Fraction> dp[10][10];
			for(int i = 0; i < n; i++)
				dp[i][i].insert(Fraction(A[i]));
			for(int i = 1; i < n; i++) {
				for(int j = 0; i + j < n; j++) {
					for(int k = j; k < j+i; k++) {
						for(set<Fraction>::iterator it = dp[j][k].begin();
							it != dp[j][k].end(); it++)
						for(set<Fraction>::iterator jt = dp[k+1][j+i].begin();
							jt != dp[k+1][j+i].end(); jt++) {
							Fraction a = *it, b = *jt;
							dp[j][j+i].insert(a+b);
							dp[j][j+i].insert(a-b);
							dp[j][j+i].insert(a*b);
							if(b.a)
								dp[j][j+i].insert(a/b);
						}
					}
				}
			}
			for(set<Fraction>::iterator it = dp[0][n-1].begin();
				it != dp[0][n-1].end(); it++)
				ret.insert(*it);
		} while(next_permutation(A, A+n));
		printf("Case %d: %d\n", ++cases, ret.size());
	}
	return 0;
}
