#include <stdio.h> 
#include <string.h>

char cube[16][16][16];
// front, left, back, right, top, bottom
void getXYZ(int N, int kind, int x, int y, int d, int &rx, int &ry, int &rz) {
	switch(kind) {
		case 0:
			rx = y, ry = d, rz = N - x - 1;
			break;
		case 1:
			rx = d, ry = N - y - 1, rz = N - x - 1;
			break;
		case 2:
			rx = N - y - 1, ry = N - d - 1, rz = N - x - 1;
			break;
		case 3:
			rx = N - d - 1, ry = y, rz = N - x - 1;
			break;
		case 4:
			rx = y, ry = N - x - 1, rz = N - d - 1;
			break;
		case 5:
			rx = y, ry = x, rz = d;
			break;
	}
}
int main() {
	char views[6][16][16];
	for(int N; scanf("%d", &N) == 1 && N; )  {
		int x, y, z;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < 6; j++)
				scanf("%s", &views[j][i]);
		}
		
		memset(cube, '?', sizeof(cube));
		
		for(int k = 0; k < 6; k++) {
			for(int i = 0; i < N; i++) {
				for(int j = 0; j < N; j++) {
					if(views[k][i][j] != '.')
						continue;
					for(int d = 0; d < N; d++) {
						getXYZ(N, k, i, j, d, x, y, z);
						cube[x][y][z] = '.';
					}
				}
			}
		}
		bool update = false;
		do {
			update = false;
			for(int k = 0; k < 6; k++) {
				for(int i = 0; i < N; i++) {
					for(int j = 0; j < N; j++) {
						if(views[k][i][j] == '.')
							continue;
						for(int d = 0; d < N; d++) {
							getXYZ(N, k, i, j, d, x, y, z);
							if(cube[x][y][z] == '.')
								continue;
							if(cube[x][y][z] == '?') {
								cube[x][y][z] = views[k][i][j];
								update = true;
								break;
							} else if(cube[x][y][z] == views[k][i][j]) {
								break;	
							} else {
								cube[x][y][z] = '.';
								update = true;
							}
						}
					}
				}
			}
		} while(update == true);
		
		int ret = 0;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				for(int k = 0; k < N; k++)
					ret += cube[i][j][k] != '.';
		printf("Maximum weight: %d gram(s)\n", ret);
	}
	return 0;
}
/*
front, left, back, right, top, bottom.
3
.R. YYR .Y. RYY .Y. .R.
GRB YGR BYG RBY GYB GRB
.R. YRR .Y. RRY .R. .Y.
2
ZZ ZZ ZZ ZZ ZZ ZZ
ZZ ZZ ZZ ZZ ZZ ZZ
0
*/
