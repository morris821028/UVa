#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 128;
unsigned long long b2[MAXN];
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m, A[1024], x, y;
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		printf("Case #%d:\n", ++cases);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);
			double sum = 0;
			for (int j = x; j <= y; j++)
				sum += log(A[j]);
			sum /= (y - x + 1);
			printf("%.9lf\n", exp(sum));
		}
	}
	return 0;
}
