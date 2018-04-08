#include <bits/stdc++.h>
using namespace std;
const int MAXS = 32;
int D;
char P[MAXS];
int f(int n) {
	int ret = 0, s = 1;
	for (int i = 0; i < n; i++) {
		if (P[i] == 'S')
			ret += s;
		else
			s <<= 1;
	}
	return ret;
}
int solve() {
	int n = strlen(P);
	if (f(n) <= D)
		return 0;
	int c = 0;
	for (int i = 0; i < n; i++)
		c += P[i] == 'S';
	if (c > D)
		return -1;
	int ret = 0;
	while (1) {
		for (int i = n-1; i > 0; i--) {
			if (P[i] == 'S' && P[i-1] == 'C') {
				swap(P[i], P[i-1]);
				break;
			}
		}
		ret++;
		if (f(n) <= D)
			return ret;
	}
	return -1;
}
int main() {
	int testcase, cases = 0;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %s", &D, P);
		printf("Case #%d: ", ++cases);
		int ret = solve();
		if (ret < 0)
			puts("IMPOSSIBLE");
		else
			printf("%d\n", ret);
	}
	return 0;
}
