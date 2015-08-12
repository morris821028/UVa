#include <bits/stdc++.h>
using namespace std;

int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, s;
		scanf("%d %d", &n, &s);
		int x[8192], y[8192], ox, oy;
		int ret = 0;
		for (int i = 0; i < n; i++)
			scanf("%d %d", &x[i], &y[i]);
		scanf("%d %d", &ox, &oy);
		
		for (int i = 0; i < n; i++) {
			if ((x[i]-ox)*(x[i]-ox)+(y[i]-oy)*(y[i]-oy) <= s*s)
				ret++;
		}
		printf("%d\n", ret);
	}
	return 0;
}
