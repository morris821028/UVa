#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		int A = 0, B = 0;
		int n, m;
		scanf("%d %d", &n, &m);
		for (int i = 0, t = m/2; i < n/2; i++) {
			if ((i&1) == 0)
				A += (t+1)/2;
			else
				A += t/2;
		}
		A *= 4;
		B = n*m-A;
		printf("Case #%d: ", ++cases);
		if (A > B)
			puts("Ana");
		else if (A == B)
			puts("Draw");
		else
			puts("Bob");
	}
	return 0;
}
