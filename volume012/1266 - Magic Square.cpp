#include<stdio.h>
#include<string.h>
int main() {
	int n, i, j, first = 0;
	while(scanf("%d", &n) == 1) {
	    if(first)   puts("");
	    first = 1;
		printf("n=%d, sum=%d\n", n, n*(n*n+1)/2);
		int map[15][15], x = 0, y = n/2;
		memset(map, 0, sizeof(map));
		for(i = 1; i <= n*n; i++) {
			if(map[x][y]) {
				x += 2, y--;
				if(x >= n)	x -= n;
				if(y < 0) 	y += n;
				map[x][y] = i;
			} else
				map[x][y] = i;
			x--, y++;
			if(x < 0)	x += n;
			if(y >= n)	y -= n;

		}
		if(n*n <= 9) {
            for(i = 0; i < n; i++, puts(""))
                for(j = 0; j < n; j++)
                    printf("%2d", map[i][j]);
		} else if(n*n >= 10 && n*n <= 100) {
            for(i = 0; i < n; i++, puts(""))
                for(j = 0; j < n; j++)
                    printf("%3d", map[i][j]);
		} else {
            for(i = 0; i < n; i++, puts(""))
                for(j = 0; j < n; j++)
                    printf("%4d", map[i][j]);
		}
	}
    return 0;
}
