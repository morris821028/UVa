#include <stdio.h>
#include <map>
#include <algorithm>
using namespace std;

int main() {
	int testcase, n, x;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		map<int, int> R;
		int low = 0;
		long long ret = 0;
		for (int i = 1; i <= n; i++) {
			scanf("%d", &x);
			int &y = R[x];
			if (y > low)	low = y;
			y = i;
			ret += i - low;
//			printf("[%d %d]\n", low + 1, i);
		}
		printf("%lld\n", ret);
	}
	return 0;
}
/*
9
3
1 2 1
5
1 2 3 1 2
4
1 2 2 1
*/
