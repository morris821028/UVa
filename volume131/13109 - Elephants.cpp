#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, n, m;
	static int A[131072];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		sort(A, A+n);
		int ret = 0;
		for (int i = 0; i < n && A[i] <= m; i++)
			ret++, m -= A[i];
		printf("%d\n", ret);
	}
	return 0;
}

