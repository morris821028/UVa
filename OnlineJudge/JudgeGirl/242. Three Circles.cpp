#include <stdio.h>
#define MAXN 65536
long long px[MAXN], py[MAXN], pn;
int has(int x, int y) {
	for (int i = 0; i < pn; i++)
		if (px[i] == x && py[i] == y)
			return 1;
	return 0;
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		long long x[3] = {}, y[3] = {}, r[3] = {};
		for (int i = 0; i < 3; i++)
			scanf("%lld %lld %lld", &x[i], &y[i], &r[i]);
			
		pn = 0;
		int ret = 0;
		for (int i = 0; i < 3; i++) {
			for (long long tx = x[i] - r[i]; tx <= x[i] + r[i]; tx++) {
				for (long long ty = y[i] - r[i]; ty <= y[i] + r[i]; ty++) {
					if (!has(tx, ty)) {
						px[pn] = tx, py[pn] = ty, pn++;
						int in = 0;
						for (int k = 0; k < 3; k++)
							in += (tx-x[k])*(tx-x[k])+(ty-y[k])*(ty - y[k]) <= r[k]*r[k];
						ret += in&1; 
					}
				}
			}
		}
		printf("%d\n", ret);
	}
	return 0;
}
/*
3
5 5 10
100 100 10
-20 -20 10

2 2 2
-4 -4 6
10 10 10

9000003 1 1
9000000 3 2
0 999999 5
*/
