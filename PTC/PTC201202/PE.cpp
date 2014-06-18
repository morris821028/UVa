#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main() {
	int n, m, i, j, k;
	while(scanf("%d %d", &n, &m) == 2) {
		int map[301][301] = {};
		for(i = 1; i <= n; i++) {
			for(j = 1; j <= m; j++) {
				scanf("%d", &map[i][j]);
				map[i][j] *= -1;
				if(map[i][j] == 0)
					map[i][j] = 1;
				else
					map[i][j]++;
			}
		}
		int max = 0, tmp;
		for(i = 1; i <= n; i++) {
			int sum[301] = {};
			for(j = i; j <= n; j++) {
				for(k = 1; k <= m; k++) {
					sum[k] = sum[k] + map[j][k];
					if(k == 1 || tmp < 0)	tmp = 0;
					tmp += sum[k];
					if(tmp > max)	max = tmp;
				}
			}
		}
		printf("%d\n", max);
	}
    return 0;
}
