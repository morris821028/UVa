#include <stdio.h> 
#include <algorithm>
using namespace std;
int test(int n, int base) {
	if (base < 2)	return 0;
	static int A[128];
	int m = 0;
	for (int i = 0; n; i++, m++)
		A[i] = n%base, n /= base;
	for (int i = 0, j = m-1; i < j; i++, j--)
		if (A[i] != A[j])
			return 0;
	return 1;
}
int main() {
	int n;
	while (scanf("%d", &n) == 1) {
		if (n == 1) {
			puts("2");
			continue;
		} else if (n == 2) {
			puts("3");
			continue;
		} 
#define INF 0x3f3f3f3f
		int ret = INF;
		for (int b = 2; b * b <= n; b++) {
			if (test(n, b)) {
				ret = b;
				break;
			}
			if (test(n, n/b - 1)) {
				ret = min(ret, n/b - 1);
			}
		}
		if (ret == INF)
			ret = n - 1;
		printf("%d\n", ret);
	}
	return 0;
}
