#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		int sum = 1, m = n;
		for (int i = 2; i <= m; i++) {
			if (m%i == 0) {
				int p = i;
				while (m%i == 0)
					m /= i, p *= i;
				sum *= (p-1)/(i-1);
			}
		}
		sum -= n;
		if (sum == n)
			puts("perfect");
		else if (sum < n)
			puts("deficient");
		else
			puts("abundant");
	}
	return 0;
}

