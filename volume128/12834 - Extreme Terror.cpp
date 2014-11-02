#include <stdio.h> 
#include <functional>
#include <algorithm>
using namespace std;
long long A[131072];
int main() {
	int testcase, cases = 0;
	int n, m;
	long long x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%lld", &A[i]), A[i] = -A[i];
		for (int i = 0; i < n; i++)
			scanf("%lld", &x), A[i] += x;
		sort(A, A+n, greater<long long>());
		long long p = 0;
		for (int i = 0, j = n - 1; i < m; i++, j--)
			if (A[j] < 0)	n--;
		for (int i = 0; i < n; i++)
			p += A[i];
		printf("Case %d: ", ++cases);
		if (p <= 0)	puts("No Profit");
		else		printf("%lld\n", p);
	}
	return 0;
}
