#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char map[1001][1001];
int main() {
	int T;
	scanf("%d", &T);
	char s[100];
	getchar();
	int rx, ry, lx, ly, i, j;
	while(T--) {
		int flag = 0, tmp;
		memset(map, 0, sizeof(map));
		while(gets(s)) {
			if(s[0] == '\0')
				break;
			sscanf(s, "%d %d %d %d", &rx, &ry, &lx, &ly);
			if(rx > lx)
				tmp = rx, rx = lx, lx = tmp;
			if(ry > ly)
				tmp = ry, ry = ly, ly = tmp;
			if(flag == 0) {
				for(i = rx; i <= lx; i++)
					for(j = ry; j <= ly; j++) {
						if(map[i][j] == 1)	flag = 1;
						map[i][j] = 1;
					}
			}
		}
		if(flag == 1)
			puts("T");
		else
			puts("F");
	}
    return 0;
}/*
3
100 180 400 230
145 145 195 395
240 275 380 375

190 150 240 300
250 250 330 300
340 150 390 400

200 50 250 200
100 200 450 250
250 250 300 450
*/
