#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <omp.h>
 
#define UINT unsigned long
#define MAXN 2048

__attribute__ ((target(mic)))
void simulate(int n, int m, char g[][MAXN][MAXN]) {
	// game of life
	int flag = 0;
	for (int it = 0; it < m; it++) {
#pragma omp parallel for
#pragma ivdep
		for (int i = 1; i <= n; i++) {
			int adj, j = 1;
#define UNLOOP { \
	adj = g[flag][i-1][j-1] + g[flag][i-1][j] + g[flag][i-1][j+1] + \
	g[flag][i  ][j-1] + g[flag][i  ][j+1] + \
	g[flag][i+1][j-1] + g[flag][i+1][j] + g[flag][i+1][j+1]; \
	g[!flag][i][j] = (g[flag][i][j] == 0 && adj == 3) || \
	(g[flag][i][j] == 1 && (adj == 2 || adj == 3)); j++; \
}
#define UNLOOP4 {UNLOOP UNLOOP UNLOOP UNLOOP}
#define UNLOOP8 {UNLOOP4 UNLOOP4}
			#pragma ivdep
			for (; j + 8 <= n; )
				UNLOOP8;
			for (; j <= n; )
				UNLOOP;
		}
		flag = !flag;
	}
}

char g[2][MAXN][MAXN];
int main() {
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		while (getchar() != '\n');

		// read input
		for (int i = 1; i <= n; i++) {
			fgets(g[0][i]+1, MAXN, stdin);
			for (int j = 1; j <= n; j++)
				g[0][i][j] -= '0';
			g[0][i][n+1] = 0;
		}
		#pragma offload target(mic) inout(g[:][:][:])
		{
			simulate(n, m, g);
		}
		// print result
		int flag = m%2;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				g[flag][i][j] += '0';
			g[flag][i][n+1] = '\0';
			puts(g[flag][i]+1);
		}
	}
	return 0;
}



