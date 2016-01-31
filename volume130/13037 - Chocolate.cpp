#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int n[3], x;
		set<int> A[3], S;
		for (int i = 0; i < 3; i++)
			scanf("%d", &n[i]);
		for (int i = 0; i < 3; i++) {
			for (int j = n[i]-1; j >= 0; j--) {
				scanf("%d", &x);
				A[i].insert(x), S.insert(x);
			}
		}
		printf("Case #%d:\n", ++cases);
		for (int i = 0; i < 3; i++) {
			int p = 0, q = 0;
			for (auto &x : A[i]) {
				int sp = 1;
				for (int j = 0; j < 3; j++) {
					if (i == j)	continue;
					if (A[j].count(x))
						sp = 0, j = 3;
				}
				if (sp)	p++;
			}
			for (auto &x : S) {
				if (A[i].count(x))
					continue;
				int sp = 1;
				for (int j = 0; j < 3; j++) {
					if (i == j)	continue;
					if (!A[j].count(x))
						sp = 0, j = 3;
				}
				if (sp)	q++;
			}
			printf("%d %d\n", p, q);
		}
	}
	return 0;
}

