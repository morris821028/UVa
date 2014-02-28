#include<stdio.h>
#define swap(x, y) {int t; t = x, x = y, y = t;}
int main() {
	char s[4] = "BCG";
	int W[6][3] = {{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
	int B[3][3], i, j, k;
	while(scanf("%d", &B[0][0]) == 1) {
		for(i = 0; i < 3; i++) {
			for(j = 0; j < 3; j++) {
				if(i+j == 0)	continue;
				scanf("%d", &B[i][j]);
			}
			swap(B[i][1], B[i][2]);
		}
		unsigned Min = 0xffffffff, idx;
		for(i = 0; i < 6; i++) {
			int tmp = 0;
			for(j = 0; j < 3; j++) {
				for(k = 0; k < 3; k++)
					if(W[i][j] != k)
						tmp += B[j][k];
			}
			if(tmp < Min)	idx = i, Min = tmp;
		}
		printf("%c%c%c %u\n", s[W[idx][0]], s[W[idx][1]], s[W[idx][2]], Min);
	}
	return 0;
}
