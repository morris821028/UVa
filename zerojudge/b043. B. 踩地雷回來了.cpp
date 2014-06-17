#include<stdio.h>
#include<stdlib.h>
int C[101][101] = {};
int Ans, n, m, B, unknow;
struct {
	int x, y;
}NUM[101];
char map[20][20], set[20][20];	
int D[8][2] = {{-1,-1},{-1,0},{-1,1},{0,-1},
				{0,1},{1,-1},{1,0},{1,1}};
void DFS(int , int);
void PASCAL(int n) {
	int i, j;
	C[0][0] = 1;
	for(i = 1; i <= n; i++) {
		C[i][0] = 1;
		for(j = 1; j <= i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
}
int Check(int x, int y) {
	static int i, k, tx, ty;
	for(i = 0, k = 0; i < 8; i++) {
		tx = x+D[i][0], ty = y+D[i][1];
		if(tx >= 0 && tx < m && ty >= 0 && ty < n) {
			if(set[tx][ty] == 1)
				k++;
		}
	}
	return k;
}
int Calu_excee(int x, int y) {
	static int i, tx, ty, total;
	for(i = 0; i < 8; i++) {
		tx = x+D[i][0], ty = y+D[i][1];
		if(tx >= 0 && tx < m && ty >= 0 && ty < n && map[tx][ty] != '_') {
			total = Check(tx, ty);
			if(total > map[tx][ty]-'0')
				return 0;
		}
	}
	return 1;
}
int Calu(int Bomb) {
	static int i, j, k, guess, tx, ty, total;
	for(i = 0, guess = 0; i < m; i++)
		for(j = 0; j < n; j++)
			if(map[i][j] == '_' && set[i][j] == 0) {
				set[i][j] = 1;
				if(Calu_excee(i, j) == 1)	{guess++;}
				set[i][j] = 0;
			}
	return C[guess][Bomb];
}
void Backtracking(int x, int y, int num, int Idx, int Bomb, int Midx) {
	if(Midx == 8 && num == 0) {
		DFS(Idx+1, Bomb);
		return;
	}
	if(Midx == 8 || 8-Midx < num)
		return;
	int tx = x+D[Midx][0], ty = y+D[Midx][1];
	if(tx >= 0 && tx < m && ty >=0 && ty < n && map[tx][ty] == '_' && set[tx][ty] == 0) {
		set[tx][ty] = 1;
		if(Calu_excee(tx, ty) == 1)
			Backtracking(x, y, num-1, Idx, Bomb-1, Midx+1);
		set[tx][ty] = 0;
		Backtracking(x, y, num, Idx, Bomb, Midx+1);
	} else {
		Backtracking(x, y, num, Idx, Bomb, Midx+1);
	}
}
void DFS(int Idx, int Bomb) {
	if(Idx == unknow) {
		Ans += Calu(Bomb);
		return;
	}
	int item = Check(NUM[Idx].x, NUM[Idx].y);
	int total = map[NUM[Idx].x][NUM[Idx].y]-'0';
	if(item > total)
		return;
	if(item == total)
		DFS(Idx+1, Bomb);
	if(item < total) {
		Backtracking(NUM[Idx].x, NUM[Idx].y, total - item, Idx, Bomb, 0);
	}
}
main() {
	PASCAL(100);
	int T, i, j, k;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d", &m, &n, &B);
		for(i = 0; i < m; i++)
			scanf("%s", map[i]);
		k = 0;
		for(i = 0; i < m; i++)
			for(j = 0; j < n; j++) {
				if(map[i][j] >= '1' && map[i][j] <= '9')
					NUM[k].x = i, NUM[k].y = j, k++;
				set[i][j] = 0;
			}
		Ans = 0, unknow = k;
		DFS(0, B);
		printf("%d\n", Ans);
	}
	return 0;
}
