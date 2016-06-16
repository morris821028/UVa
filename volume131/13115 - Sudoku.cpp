#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d", &n);
		for (m = 1; m*m < n; m++);
		
		int ret = 1, x;
		int mark[3][32][32] = {};
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				scanf("%d", &x);
				mark[0][i][x]++;
				ret &= mark[0][i][x] == 1;
				mark[1][j][x]++;
				ret &= mark[1][j][x] == 1;
				mark[2][i/m*m+j/m][x]++;
				ret &= mark[2][i/m*m+j/m][x] == 1;
			}
		}
		puts(ret ? "yes" : "no");
	}
	return 0;
}

