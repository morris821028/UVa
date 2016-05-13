#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, x, m = 0;
		int A[32];
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%d", &A[i]), m += A[i];
		printf("Case #%d:", ++cases);
		while (m) {
			map<int, int> R;
			for (int i = 0; i < n; i++)
				R[A[i]]++;
			R[0]++, R[0]--;
			pair<int, int> m1 = *R.rbegin();
			R.erase(m1.first);
			pair<int, int> m2 = *R.rbegin();
			R.erase(m2.first);
			putchar(' ');
			if (m1.second > 2 || m1.second == 1) {
				int v = 0;
				for (int i = 0; i < n; i++) {
					if (A[i] == m1.first) {
						putchar('A' + i), A[i]--, m--;
						v++;
						if (v == 1)
							break;
					}
				}
			} else if (m1.second == 2) {
				int v = 0;
				for (int i = 0; i < n; i++) {
					if (A[i] == m1.first) {
						putchar('A' + i), A[i]--, m--;
						v++;
						if (v == 2)
							break;
					}
				}
			}
		}
		puts("");
	}
	return 0;
}
/*
4
2
2 2
3
3 2 2
3
1 1 2
3
2 3 1
*/
