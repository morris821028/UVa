#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main() {
	int n, cases = 0;
	while (scanf("%d", &n) == 1) {
		int w[105] = {}, h[105] = {};
		int x, y, f = 0;
		for (int i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			w[x] = h[y] = 1;
			if (x == y)	f = 1;
		}
		int ret = 0x3f3f3f3f;
		for (int i = 0; i <= 100; i++) {
			if (w[i])
			for (int j = 0; j <= 100; j++) {
				if (h[j])
					ret = min(ret, abs(i-j));
			}
		}
		if (f == 0)
			ret += ret == 0;
		printf("Case %d : %d\n", ++cases, (ret + 1)/2);
	}
	return 0;
}
/*
3
35 40
30 35
32 44
3
35 68
70 1
79 25
*/
