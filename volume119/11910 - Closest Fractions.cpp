#include <stdio.h>
#include <math.h>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
using namespace std;

class Frac {
	public:
	int x, y;
	Frac(int a = 0, int b = 0):
		x(a), y(b) {}
	double toDouble() const {
		return (double) x/y;
	}
	bool operator<(const Frac &a) const {
		return toDouble() < a.toDouble();
	}
} D[1048576];
double DD[1048576];
double cmpv;
bool cmp(Frac a, Frac b) {
	return fabs(a.toDouble() - cmpv) < fabs(b.toDouble() - cmpv);
}
int f(double v) {
	if (v >= 1000)	return 4;
	if (v >= 100)	return 3;
	if (v >= 10)	return 2;
	return 1;
}
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out.txt", "w+t", stdout); 
	int n = 0;
	for (int y = 1; y <= 1000; y++) {
		for (int x = 1; x <= 1000; x++) {
			if (__gcd(x, y) == 1)
				D[n++] = Frac(x, y);
		}
	}
	sort(D, D + n);
	for (int i = 0; i < n; i++)
		DD[i] = D[i].toDouble();
	char s[32];
	double v;
	while (scanf("%s", s) == 1) {
		printf("Input : %s\n", s);
		sscanf(s, "%lf", &v);
		int pos = lower_bound(DD, DD + n, v) - DD;
		vector<Frac> A;
		for (int i = max(0, pos - 6); i < min(n, pos + 6); i++)
			A.push_back(D[i]);
		cmpv = v;
		sort(A.begin(), A.end(), cmp);
		for (int i = 0, j = 1; i < 3 && i < A.size(); i++, j++)
			printf("    %d : %*.*lf = %4d / %d\n", j, f(A[i].toDouble()), 10 - f(A[i].toDouble()), A[i].toDouble(), A[i].x, A[i].y);
	}
	return 0;
}
