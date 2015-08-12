#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m, A[505];
		scanf("%d %d", &n, &m);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]);
		for (int i = 0; i < m; i++) {
			int cmd, x, y;
			scanf("%d", &cmd);
			if (cmd == 1) {
				scanf("%d %d", &x, &y);
				if (x > y)	swap(x, y);
				int ret = A[x];
				for (int i = x; i <= y; i++)
					ret = max(ret, A[i]);
				printf("%d\n", ret);
			} else if (cmd == 2) {
				scanf("%d %d", &x, &y);
				if (x > y)	swap(x, y);
				int ret = 0;
				for (int i = x; i <= y; i++)
					ret += A[i];
				printf("%d\n", ret / (y-x+1));
			} else {
				scanf("%d", &x);
				printf("%d\n", A[x]);
			}
		}
	}
	return 0;
}
