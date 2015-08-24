#include <bits/stdc++.h> 
using namespace std;
const int MAXN = 128;
unsigned long long b2[MAXN];
int f(long long n, int m, int s) {
	if (m == 1)	return s;
	if (n <= b2[m-1])
		return f(n, m-1, s);
	if (n == b2[m-1]+1)
		return s;
	return f(b2[m-1]-(n-b2[m-1]-1)+1, m-1, !s);
}
int main() {
	b2[0] = 0;
	for (int i = 1; i < MAXN; i++)
		b2[i] = (b2[i-1]<<1)+1;
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		long long n;
		scanf("%lld", &n);
		printf("Case #%d: ", ++cases);
		for (int i = 0; i < MAXN; i++) {
			if (b2[i] >= n) {
				printf("%d\n", f(n, i, 0));
				break;
			}
		}
	}
	return 0;
}
