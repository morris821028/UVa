#include <stdio.h>

int main() {
	int i, j, t, n, k, r, x, y;
	long long int max;
	long long int map[100][100];
	long long int cnt[100][100];
	int rec[4][2] = {{-1, 0}, {+1, 0}, {0, -1}, {0, +1}};
	
	while(scanf("%d %d", &n, &k) == 2) {
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				cnt[i][j] = 0;
		
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%lld", &map[i][j]);
		
		max = -2147483647;
		cnt[0][0] = map[0][0];
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				for(r = 0; r < 4; r++)
					for(t = 1; t <= k; t++) {
						x = i+rec[r][0]*t;
						y = j+rec[r][1]*t;
						
						if(x >= 0&&y >= 0&&x < n&&y < n&&map[x][y] > map[i][j]) {
							if(cnt[i][j]+map[x][y] > cnt[x][y])
								cnt[x][y] = cnt[i][j]+map[x][y];
							
							if(cnt[x][y] > max)
								max = cnt[x][y];
						}
					}
		
		printf("%lld\n", max);
	}
	
	return 0;
}

