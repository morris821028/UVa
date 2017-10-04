#include <stdio.h>
#include <limits.h>
#define max(x, y) ((x)>(y)?(x):(y))
int main() {
	int n, m;
	static int tb[512][512][2], tk[512], st[512];
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &st[i], &tk[i]);
			for (int j = 0; j < tk[i]; j++)
				scanf("%d %d", &tb[i][j][0], &tb[i][j][1]);
		}
		int cm[512] = {}, ret[512] = {}, idx[512] = {};
		while (1) {
			int mn = INT_MAX, mn_arg;
			for (int i = 0; i < m; i++) {
				if (idx[i] == tk[i])
					continue;
				int j = idx[i];
				int ctime = max(max(cm[tb[i][j][0]], st[i]), ret[i]) + tb[i][j][1];
				if (ctime < mn)
					mn = ctime, mn_arg = i;
			}
			if (mn == INT_MAX)
				break;
			int i = mn_arg, j = idx[mn_arg];
//			printf("Job %d Task %d\n", i, j);
			ret[i] = cm[tb[i][j][0]] 
					= max(max(cm[tb[i][j][0]], st[i]), ret[i]) + tb[i][j][1];
			idx[i]++;
		}
		for (int i = 0; i < m; i++)
			printf("%d\n", ret[i]);
	}
	return 0;
}

