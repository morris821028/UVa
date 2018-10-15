#include <stdio.h>

static inline void online_printInt(int x) {
    static char ch[16];
    static int idx;
    idx = 0;
    if (x == 0)	ch[++idx] = 0;
    while (x > 0) ch[++idx] = x % 10, x /= 10;
    while (idx) 
        putchar(ch[idx--]+48);
}

int main() {
	int n, k, x, y;
	static int g[1000][1000];
	scanf("%d %d %d %d", &n, &k, &x, &y);
	x += (k-1), y -= (k-1);
	x = (x%n+n)%n, y = (y%n+n)%n;
	for (int i = 1; i <= n*n; i++) {
		g[x][y] = i;
		x--, y++;
		if (x < 0)	x = n-1;
		if (y >= n)	y = 0;
		if (g[x][y]) {
			x += 2, y--;
			if (x >= n)
				x = x%n;
			if (y < 0)
				y = n-1;
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			online_printInt(g[i][j]);
			putchar(j == n-1 ? '\n' : ' ');
//			printf("%d%c", g[i][j], " \n"[j==n-1]);
		}
	}
	return 0;
}
