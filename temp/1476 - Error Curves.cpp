#include <stdio.h> 
#include <algorithm>
using namespace std;
#define MAXN 10005
double a[MAXN], b[MAXN], c[MAXN];
double f(double x, int n) { 
	double ret = a[0] * x * x + b[0] * x + c[0];
	for (int i = 1; i < n; i++) {
		double t = a[i] * x * x + b[i] * x + c[i];
		ret = max(ret, t);
	}
	return ret;
} 
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf %lf %lf", &a[i], &b[i], &c[i]);
		
		double l = 0, r = 1000, mid, midmid;
		double md, mmd, ret = f(0, n);
		for (int it = 0; it < 100; it++) {
			mid = (l + r) /2;
			midmid = (mid + r)/2;
			md = f(mid, n), mmd = f(midmid, n);
			ret = min(ret, md);
			if (md < mmd)
				r = midmid;
			else
				l = mid;
		}
		printf("%.4lf\n", ret);
	}
	return 0;
}
