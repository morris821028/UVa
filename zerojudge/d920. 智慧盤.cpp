#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct status {
	int board[4][4];
	int px, py;
}init, target = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,3,3};
int pos[17][2], MaxDepth, flag;
int step[4][2] = {{-1,0}, {0,-1},{0,1},{1,0}};/*u l r d*/
void Swap(int *x, int *y) {
	int t;
	t = *x, *x = *y, *y= t;
}
int H() {
	int sum = 0, tmp, a, b;
	for(a = 0; a < 4; a++) {
		for(b = 0; b < 4; b++) {
			tmp = init.board[a][b];
			if(tmp < 16)
				sum += abs(a-pos[tmp][0]) + abs(b-pos[tmp][1]);
		}
	}
	return sum;
}
int SingleH(int x, int y, int tmp) {
	return abs(x-pos[tmp][0]) + abs(y-pos[tmp][1]);
}
int IDAstar(int dv, int hv, int prev) {
	if(hv == 0) { flag = dv;return dv; }
	if(dv + hv > 10 || dv + hv > MaxDepth)	return dv + hv;

	int a, nx, ny, x = init.px, y = init.py;
	int tMaxDepth = 10000, dn, ht;
	
	for(a = 0; a < 4; a++) {
		if(a + prev == 3) continue;
		nx = x + step[a][0], ny = y + step[a][1];
		if(nx < 0 || nx == 4 || ny < 0 || ny == 4)
			continue;
		
		ht = hv - SingleH(nx, ny, init.board[nx][ny]) + SingleH(x, y, init.board[nx][ny]);
		Swap(&init.board[x][y], &init.board[nx][ny]);
		init.px = nx, init.py = ny;
		dn = IDAstar(dv+1, ht, a);
		Swap(&init.board[x][y], &init.board[nx][ny]);
		init.px = x, init.py = y;
		if(flag)	return dv;
		if(tMaxDepth > dn) tMaxDepth = dn;
	}
	return tMaxDepth;
}
main() {
	int T, a, b, ini;
	int index = 0;
	for(a = 0; a < 4; a++)
		for(b = 0; b < 4; b++) {
			scanf("%d", &init.board[a][b]);
			if(init.board[a][b] == 0) {
				init.board[a][b] = 16;
				init.px = a, init.py = b;
			}
			index++;
			pos[index][0] = a, pos[index][1] = b;
		}
	if(H()) {
		MaxDepth = H(), flag = 0, ini = MaxDepth;
		while((flag == 0) && (MaxDepth <= 10))
			MaxDepth = IDAstar(0, ini, -1);
		if(flag)
			printf("%d\n", flag);
		else
			puts("TOO LONG");
	}
	else puts("0");
	return 0;
}
