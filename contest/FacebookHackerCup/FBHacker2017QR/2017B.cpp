#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n;
		vector<int> A;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			int x;
			scanf("%d", &x);
			A.push_back(x);
		}
		sort(A.begin(), A.end());
		int ret = 0;
		int r = n-1, l = 0;
		while (r >= l) {
			int need = ((50 + A[r]-1) / A[r]);
			if (l + need-1 > r)
				break;
			l += need-1, r--;
			ret++;
		}
		printf("Case #%d: %d\n", ++cases, ret);
	}
	return 0;
}

