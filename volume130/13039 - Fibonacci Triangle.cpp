#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		long long A[1024];
		for (int i = 0; i < n; i++)
			scanf("%lld", &A[i]);
		
		long long ret = 0, prev = 0;
		for (int i = 0; i < n; i++) {
			while (prev > 0 && A[i] >= 2)
				ret++, prev--, A[i] -= 2;
			ret += A[i]/3;
			A[i] %= 3;
			if (i+1 < n && A[i] == 2 && A[i+1])
				ret++, A[i+1]--, A[i] = 0;
			if (i+1 < n && A[i] == 1 && A[i+1] > 1)
				ret++, A[i+1] -= 2, A[i] = 0;
			prev += A[i];
		}
		printf("%lld\n", ret);
	}
	return 0;
}

