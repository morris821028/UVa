#include <bits/stdc++.h>
using namespace std;
const long double PI = acos(-1), e = exp(1);
const int MAXN = 100001;
double f[MAXN];
double stirling(int n) {
	if (n < MAXN)
		return f[n];
	return log2(sqrt(2*PI*n)) + n*log2(n/e);
}
double logC(int n, int m) {
	return stirling(n) - stirling(n - m) - stirling(m);
}
int main() {
	f[0] = 0;
	for (int i = 1; i < MAXN; i++)
		f[i] = log2(i) + f[i-1];
	int n, a, b;
	int cases = 0;
	while (scanf("%d %d %d", &n, &a, &b) == 3) {
		double ret = 0;
		for (int i = a; i <= b; i++)
			ret += pow(2, logC(n, i) - log2(2) * n);
		printf("%.4lf\n", ret);
		if (++cases > 100)
			break;
	}
    return 0;
} 
