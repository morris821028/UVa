#include<stdio.h>
main() {
	int n, m;
	while(scanf("%d %d", &n, &m) == 2) {
		int Map[51][51] = {}, x, y, a;
		char D[2], s[101];
		while(scanf("%d %d %s %s", &x, &y, D, s) == 4) {
			int lost = 0, face;
			switch(D[0]) {
				case 'N':face = 0;break;
				case 'E':face = 1;break;
				case 'S':face = 2;break;
				default:face = 3;
			}
			for(a = 0; s[a] && lost == 0; a++) {
				switch(s[a]) {
					case 'R':face = (face+1)%4;break;
					case 'L':face = (face+3)%4;break;
					default: {
						switch(face) {
							case 0:y++;break;
							case 1:x++;break;
							case 2:y--;break;
							default:x--;
						}
						if(x < 0 && Map[x+1][y] == 0) {
							lost = 1, Map[x+1][y] = 1, x++;
						}
						if(x > n && Map[x-1][y] == 0) {
							lost = 1, Map[x-1][y] = 1, x--;
						}
						if(y < 0 && Map[x][y+1] == 0) {
							lost = 1, Map[x][y+1] = 1, y++;
						}
						if(y > m && Map[x][y-1] == 0) {
							lost = 1, Map[x][y-1] = 1, y--;
						}
					}
				}
				if(x < 0) x++;
				if(y < 0) y++;
				if(x > n) x--;
				if(y > m) y--;
			}
			switch(face) {
				case 0:face = 'N';break;
				case 1:face = 'E';break;
				case 2:face = 'S';break;
				default:face = 'W';
			}
			if(lost)
				printf("%d %d %c LOST\n", x, y, face);
			else
				printf("%d %d %c\n", x, y, face);
		}
	}
	return 0;
}
