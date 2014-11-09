#include <stdio.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase, H1, S1, H2, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d %d", &H1, &S1, &H2);
		int a = S1 * (H2 - 1), b = H1 - 1, g;
		g = __gcd(a, b);
		a /= g, b /= g;
		printf("Case %d:", ++cases);
		if (a/b > 0)	printf(" %d", a/b);
		if (a%b)		printf(" %d/%d", a%b, b);
		puts("");
	}
	return 0;
}
