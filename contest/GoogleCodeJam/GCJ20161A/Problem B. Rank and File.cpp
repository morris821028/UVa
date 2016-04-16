#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m, x;
		map<int, int> R;
		scanf("%d", &n);
		m = 2*n-1;
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &x);
				R[x]++;
			}
		}
		printf("Case #%d:", ++cases);
		for (auto e : R) {
			if (e.second % 2 == 1)
				printf(" %d", e.first);
		}
		puts("");
	}
	return 0;
}

