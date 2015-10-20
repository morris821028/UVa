#include <stdio.h>
int y_valid[32] = {};
int dfs(int lv, int row, int dia1, int dia2, int mask) {
    if (row == mask)
    	return 1;
    int pos = mask & (~(row | dia1 | dia2)) & y_valid[lv], p;
    int ret = 0;
    while (pos) {
        p = pos & (-pos);
        pos -= p;
        ret += dfs(lv+1, row|p, (dia1|p)<<1, (dia2|p)>>1, mask);
    }
	return ret;
}
int totalNQueens(int n) {
	int sum = 0;
	int chunk = 1;
	int row = 0, dia1 = 0, dia2 = 0, mask = (1<<n)-1, lv = 0;
	int pos = mask & (~(row | dia1 | dia2)) & y_valid[0], p;
	#pragma omp parallel for schedule(dynamic, chunk) reduction(+:sum)
	for (int i = 0; i < n; i++) {
		if ((pos>>i)&1) {
			p = 1<<i;
			int t = dfs(lv+1, row|p, (dia1|p)<<1, (dia2|p)>>1, mask);
			sum += t;
		}
	}
	return sum;
}
int main() {
	int cases = 0, n;
	char s[32] = {};
	while (scanf("%d", &n) == 1 && n) {
		for (int i = 0; i < n; i++) {
			scanf("%s", s);
			y_valid[i] = (1<<n)-1;
			for (int j = 0; j < n; j++) {
				if (s[j] == '*')
					y_valid[i] ^= (1<<j);
			}
		}
		int ret = totalNQueens(n);
		printf("Case %d: %d\n", ++cases, ret);
	}
	return 0;
}
