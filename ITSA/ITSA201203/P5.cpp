#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main() {
	int t, n, m;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &m);
		int map[16][16] = {}, used[16][16] = {};
		int x, y, i, j;
		int d, num = n*n;
		if(n%2 == 1) {
			x = -1, y = -1;
			d = 3;
		} else {
			x = n, y = n;
			d = 1;
		}
		while(num > 0) {
			if(d == 1) {
				x--, y--;
				for(i = x; i >= 0; i--) {
					if(used[i][y] == 1)	{break;}
					used[i][y] = 1;
					map[i][y] = num--;
					x--;
				}
			}
			if(d == 2) {
				y++, x--;
				for(i = y; i < n; i++) {
					if(used[x][i] == 1) {break;}
					used[x][i] = 1;
					map[x][i] = num--;
					y++;
				}
			}
			if(d == 3) {
				y++, x++;
				for(i = x; i < n; i++) {
					if(used[i][y] == 1) {break;}
					used[i][y] = 1;
					map[i][y] = num--;
					x++;
				}
			}
			if(d == 4) {
				x++, y--;
				for(i = y; i >= 0; i--) {
					if(used[x][i] == 1) {break;}
					used[x][i] = 1;
					map[x][i] = num--;
					y--;
				}
			}
			if(d == 1)
				d = 4;
			else if(d == 2)
				d = 1;
			else if(d == 3)
				d = 2;
			else
				d = 3;/*
			for(i = 0; i < n; i++, puts(""))
				for(j = 0; j < n; j++)
					printf("%2d", map[i][j]);
			printf("%d %d\n", x, y);
			system("pause");*/
		}
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				if(map[i][j] == m)
					x = i, y = j;
		int flag = 0;
		for(i = -1; i <= 1; i++) {
			for(j = -1; j <= 1; j++)
				if(x+i < 0 || x+i >= n || y+j < 0 || y+j >= n)
					flag = 1;
		}
		if(flag == 1)
			puts("No answer");
		else {
			for(i = -1; i <= 1; i++) {
				for(j = -1; j <= 1; j++) {
					if(j != -1)
						printf(" ");
					printf("%d", map[x+i][y+j]);
				}
				puts("");
			}
		}
		if(t)
			puts("");
	}
    return 0;
}
