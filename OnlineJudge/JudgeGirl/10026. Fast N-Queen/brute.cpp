#include <stdio.h>
int y_valid[32] = {}, ret = 0;
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
    return dfs(0, 0, 0, 0, (1<<n)-1);
}
int main() {
	int n, cases = 0;
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
		printf("Case %d: %d\n", ++cases, totalNQueens(n));
	}
	return 0;
}
