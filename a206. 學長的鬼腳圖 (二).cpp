#include<stdio.h>
main() {
	int n, m, t, a, b, c, temp;
	int test[1000][65], t2[65];
	char map[65][257];
	for(a = 0; a < 257; a++)	map[0][a] = '-';
	while(scanf("%d %d", &n, &m) == 2) {
		scanf("%d", &t);
		for(a = 0; a < t; a++)
			for(b = 1; b <= n; b++)
				scanf("%d", &test[a][b]);
		for(a = 1, getchar(); a <= n; a++)		gets(map[a]);
		int flag = 1, tmp, u;
		for(a = 0; a < t; a++) {
			for(b = 0; b < m; b++, c = 1) {
				while(c <= n) {
					while(map[c][b] == '-' && c <= n)	c++;
					u = c, c++;
					while(map[c][b] == map[c-1][b] && c <= n) c++;
					if(test[a][u] > test[a][c-1])	tmp = test[a][u], test[a][u] = test[a][c-1], test[a][c-1] = tmp;
					while(map[c][b] == '-' && c <= n)	c++;
				}
			}
			for(c = 2; c <= n && flag; c++)
				if(test[a][c] < test[a][c-1])
					flag = 0;
		}			
		if(flag)	puts("This is a reliable sorting ghost leg!");
		else		puts("So sad......This is just a  ghost leg.");
	}
	return 0;
}
