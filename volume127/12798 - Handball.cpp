#include <stdio.h>

int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		int ret = 0, x;
		for (int i = 0; i < n; i++) {
			int ok = 1;
			for (int j = 0; j < m; j++) {
				scanf("%d", &x);
				ok &= x > 0;
			}
			ret += ok;
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
5 3
0 0 0
1 0 5
0 0 0
0 1 2
1 1 0
12 5
4 4 2 3 7
0 0 0 1 0
7 4 7 0 6
1 2 3 3 2
0 0 0 0 0
4 0 9 10 10
0 1 0 0 0
1 2 0 2 3
10 10 10 1 0
0 3 3 3 4
10 10 0 10 10
1 1 2 0 9
*/
