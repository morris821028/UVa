#include<stdio.h>
#include<stdlib.h>
/*black 1a white 0A*/
char Map[8][9];
int bkx, bky, wkx, wky;
int D[8][2]={{0,1},{0,-1},
			 {1,0},{-1,0},
			 {1,1},{1,-1},
			 {-1,1},{-1,-1}
			};
int S[8][2]={{2,1},{2,-1},
			 {-2,1},{-2,-1},
			 {1,2},{1,-2},
			 {-1,2},{-1,-2}
			};
int find(int x, int y, int Dx, int Dy, int w, int a) {
	int t = 1;
	do {
		if(Map[x][y] != '.') {
			int p = (Map[x][y] >= 'a');
			if(p != w) return 0;
			else {
				int tp = Map[x][y] - p * ('a'-'A');
				switch(tp) {
					case 'P':{if(w == 0) {
									if((a == 4 || a == 5) && t == 1)
										return 1;
								}
							else {
									if((a == 6 || a == 7) && t == 1)
										return 1;
								}
							}break;
					case 'R':if(a < 4) return 1;break;
					case 'B':if(a > 3) return 1;break;
					case 'Q':return 1;break;
				}
				return 0;
			}
		}
		x += Dx, y += Dy, t++;
	}
	while(x >=0 && y >=0 && x < 8 && y < 8);
	return 0;
}
int Check(int x, int y, int who) {
	if(bkx < 0 || wkx < 0) return 0;
	int a, r = 0;
	for(a = 0; a < 8; a++) {
		r = find (x+D[a][0], y+D[a][1], D[a][0], D[a][1], who, a);
		if(r) break;
	}
	for(a = 0; a< 8; a++) {
		int xx = x + S[a][0], yy = y + S[a][1];
		if(xx < 0 || xx > 7 || yy < 0 || yy > 7) continue;
		if(Map[xx][yy] == 'n' || Map[xx][yy] == 'N') {
			int p = Map[xx][yy] == 'n';
			if(p == who) return 1;
		}
	}
	return r;
}
main() {
	int C = 0, a, b;
	while(1) {
		char flag = 1;
		int bkx = -1, bky = -1, wkx = -1, wky = -1;
		for(a = 0; a < 8; a++) {
			scanf("%s", &Map[a]);
			for(b = 0; b < 8; b++) {
				if(Map[a][b] != '.') flag = 0;
				if(Map[a][b] == 'k') bkx = a, bky = b;
				if(Map[a][b] == 'K') wkx = a, wky = b;
			}
		}
		if(flag == 1) break;
		printf("Game #%d: ", ++C);
		if(Check(wkx, wky, 1))
			puts("white king is in check.");
		else if(Check(bkx, bky, 0))
			puts("black king is in check.");
		else puts("no king is in check.");
	}
	return 0;
}
