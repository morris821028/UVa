#include <bits/stdc++.h>
using namespace std;

int R[32767];
int main() {
	int testcase, cases = 0;
	int n, x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++)
			scanf("%d", &x), R[x] = i;
			
		int ret = 0, pos = -1;
		for (int i = 1; i <= n; i++) {
			if (R[i] < pos) {
				ret++;
				pos = n+1;
			} else {
				pos = R[i];
			}
		}
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}

