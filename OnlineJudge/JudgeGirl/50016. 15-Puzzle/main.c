#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
/* u, l, r, d */
#define MAXN 4
const int dir[4][2] = {{-1,0}, {0,-1}, {0,1}, {1,0}};

bool solvable(int g[][MAXN]) {
	int sum, row;
	sum = row = 0;
	for (int i = 0; i < MAXN*MAXN; i++) {
		if (g[i/4][i%4] == 0) {
			row = i/4 + 1;
			continue;
		}
		for (int j = i+1; j < MAXN*MAXN; j++) {
			if (g[j/4][j%4] < g[i/4][i%4] && g[j/4][j%4])
				sum++;
		}
	}
	return 1 - (sum + row)%2;
}

int Htable[4][4][16], g[MAXN][MAXN];
int Hinit(int g[][MAXN]) {
	int pos[MAXN*MAXN][2];
	for (int i = 0, k = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            pos[++k][0] = i, pos[k][1] = j;
    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            for (int k = 1; k < MAXN*MAXN; k++)
                Htable[i][j][k] = abs(i - pos[k][0]) + abs(j - pos[k][1]);
                
    int sum = 0, x;
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < MAXN; j++) {
            x = g[i][j];
            if (x)
            	sum += abs(i-pos[x][0]) + abs(j-pos[x][1]);
        }
    }
    return sum;
}

// IDA
int ida_depth, solved;
int min(int x, int y) {return x < y ? x : y;}
void swap(int *x, int *y) {int t; t = *x, *x = *y, *y = t;}
int IDA(int dep, int ox, int oy, int hv, int pred) {
	if (hv == 0) {
		solved = dep;
		return dep;
	}
	if (dep + hv > ida_depth)
		return dep + hv;
	int mndep = INT_MAX, shv;
	for (int i = 0; i < 4; i++) {
		if (i + pred == 3)
			continue;
		int tx = ox + dir[i][0];
		int ty = oy + dir[i][1];
		if (tx < 0 || ty < 0 || tx >= MAXN || ty >= MAXN)
			continue;
		
		shv = hv;
		shv -= Htable[tx][ty][g[tx][ty]];
		shv += Htable[ox][oy][g[tx][ty]];
		swap(&g[tx][ty], &g[ox][oy]);
		int vdep = IDA(dep+1, tx, ty, shv, i);
		swap(&g[tx][ty], &g[ox][oy]);
		if (solved)	return solved;
		mndep = min(mndep, vdep);
	}
	return mndep;
}
int main() {
	int K, ox, oy;
	while (scanf("%d", &K) == 1) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				scanf("%d", &g[i][j]);
				if (g[i][j] == 0)
					ox = i, oy = j;
			}
		}
		
		if (!solvable(g)) {
			puts("0");
		} else {
			int baseH;
			solved = 0, ida_depth = baseH = Hinit(g);
			if (ida_depth == 0) {
				puts("1");
//				puts("0");
			} else {
				while (solved == 0 && ida_depth <= K)
					ida_depth = IDA(0, ox, oy, baseH, -1);
				if (solved && solved <= K)
					puts("1");
				else
					puts("0");
				
//				 printf("%d\n", solved);
			}
		}
	}
	return 0;
}
/*
10
2 3 4 0
1 5 7 8
9 6 10 12
13 14 11 15

20
13 1 2 4
5 0 3 7
9 6 10 12
15 8 11 14

2
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 0 

100
6 2 8 4
12 14 1 10
13 15 3 9
11 0 5 7

100
6 8 4 2
12 14 1 10
13 15 3 9
11 0 5 7
*/
