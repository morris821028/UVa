#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	int n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		printf("Case #%d: %d\n", ++cases, n*2-1);
	}
	return 0;
}

