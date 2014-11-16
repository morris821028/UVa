#include <stdio.h> 
// Pick's theorem, A = i + b/2 - 1
int main() {
	char g[128][128];
	int n, m;
	while (scanf("%d %d", &n, &m) == 2) {
		for (int i = 0; i < n; i++)
			scanf("%s", g[i]);
		int B = 0, I = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (g[i][j] == '/' || g[i][j] == '\\')
					B++;
			}
		}
		
		for (int i = 0; i <= n; i++) {
			int in = 0;
			for (int j = 0; j <= m; j++) {
				int f = 0;
				if (i-1 >= 0 && g[i-1][j] == '/' && g[i][j] == '\\')
					in++;
				if (i-1 >= 0 && j-1 >= 0 && g[i-1][j-1] == '\\' && g[i][j-1] == '/')
					in++;
				if (i-1 >= 0 && j-1 >= 0 && g[i-1][j-1] == '\\' && g[i][j] == '\\')
					in++;
				if (i-1 >= 0 && j-1 >= 0 && g[i-1][j] == '/' && g[i][j-1] == '/')
					in++;
				if (i-1 >=0 && j-1 >= 0 && g[i-1][j-1] == '\\')	f = 1;
				if (i-1 >=0 && g[i-1][j] == '/')				f = 1;
				if (g[i][j] == '\\')							f = 1;
				if (j-1 >= 0 && g[i][j-1] == '/')				f = 1;
				if (!f && in%2 == 1)
					I ++;
			}
		}
		printf("%d\n", I + B/2 - 1);
	}
	return 0;
}
