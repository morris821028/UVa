#include <stdio.h> 
#include <math.h>
#include <assert.h>
#include <algorithm>
using namespace std;
const int MAXN = 1024;

double LV[MAXN], H[MAXN], W[MAXN], D[MAXN], V;

void solve(int n, double V) {
	double l = 0, r = 0, mid;
	double sumV = 0;
	for (int i = 0; i < n; i++) {
		sumV += H[i] * W[i] * D[i];
		r = max(r, LV[i] + H[i]);
	}
	if (sumV < V) {
		puts("OVERFLOW");
		return ;
	}
	
	for (int it = 0; it < 100; it++) {
		mid = (l + r)/2;
		sumV = 0;
		for (int i = 0; i < n; i++) {
			if (mid < LV[i])	continue;
			sumV += W[i] * D[i] * min(H[i], mid - LV[i]);
		}
		if (sumV > V)
			r = mid;
		else
			l = mid;
	}
	printf("%.2lf\n", l);
}
int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		assert(n < MAXN);
		for (int i = 0; i < n; i++)
			scanf("%lf %lf %lf %lf", &LV[i], &H[i], &W[i], &D[i]);
		scanf("%lf", &V);
	
		solve(n, V);
		if (testcase)	puts("");
	}
	return 0;
} 
