#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>

#define UINT unsigned long
#define MAXN 2048
#define MAXM ((MAXN*MAXN)>>5)+1
#define GET(i, x, y) (g[i][(x<<11|y)>>5]>>((x<<11|y)&31)&1)
#define SET(i, x, y) (g[i][(x<<11|y)>>5] |= 1<<((x<<11|y)&31))
#define RESET(i, x, y) (g[i][(x<<11|y)>>5] &= ~(1<<((x<<11|y)&31)))
int g[2][MAXM];
int n, m;
int main() {
	while (scanf("%d %d", &n, &m) == 2) {
		while (getchar() != '\n');
		
		memset(g, 0, sizeof(g));
		// read input
		for (int i = 1; i <= n; i++) {
			static char s[MAXN];
			fgets(s+1, MAXN, stdin);
			for (int j = 1; j <= n; j++) {
				if (s[j] == '1')
					SET(0, i, j);
			}
		}
		
		// game of life
		int flag = 0;
		int chunk = 32;
		for (int it = 0; it < m; it++) {
//			#pragma omp parallel for schedule(static, chunk)
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++) {
					int adj = GET(flag, i-1, j-1) + GET(flag, i-1, j) + GET(flag, i-1, j+1)
							+ GET(flag, i, j-1) + GET(flag, i, j+1)
							+ GET(flag, i+1, j-1) + GET(flag, i+1, j) + GET(flag, i+1, j+1);
					int t = (GET(flag, i, j) == 0 && adj == 3) ||
							(GET(flag, i, j) == 1 && (adj == 2 || adj == 3));
					if (t)
						SET(!flag, i, j);
					else
						RESET(!flag, i, j);
				}
			}
			flag = !flag;
		}
		
		// print result
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				putchar(GET(flag, i, j) ? '1' : '0');
			puts("");
		}
	}
	return 0;
}

