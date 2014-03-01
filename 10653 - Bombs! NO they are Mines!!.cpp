#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxL 1000
int map[maxL][maxL], L, dx2, dy2;
int sx, sy, ex, ey, R, C;
struct Heap {
	long long F;
	short x, y;
} Heap[maxL*maxL], T;
void Swap(int P, int S) {
	static struct Heap T;
	T = Heap[P], Heap[P] = Heap[S], Heap[S]= T;
}
void siftUp(int set) {
	static int S, P;
	S = set, P = set>>1;
	while(S >= 2 && Heap[P].F > Heap[S].F)
		Swap(P, S), S = P, P = S>>1;
}
void siftDown(int set) {
	static int S, P;
	S = set<<1, P = set;
	while(S <= L) {
		if(S < L && Heap[S+1].F < Heap[S].F)
			S++;
		if(Heap[P].F <= Heap[S].F)
			break;
		Swap(P, S), P = S, S = P<<1;
	}
}
void insVal(int set, long long F, int x, int y) {
	Heap[set].F = F;
	Heap[set].x = x, Heap[set].y = y;
	siftUp(set);
}
void delMin() {
	Swap(1, L), L--;
	siftDown(1);
}
long long H(int cx, int cy) {
	static int dx1, dy1;
	dx1 = cx-ex, dy1 = cy-ey;
	return ((abs(cx-ex)+abs(cy-ey))<<20) + abs(dx1*dy2-dx2*dy1);
}
void Expand(int nx, int ny, int cx, int cy) {
	if(nx < 0 || ny < 0 || nx >= R || ny >= C)
		return;
	
	if(map[nx][ny] != -1 && map[nx][ny] == 0) {
		map[nx][ny] = map[cx][cy]+1;
		L++, insVal(L, (map[nx][ny]<<20)+H(nx, ny), nx, ny);
	}
}
void AStar() {
	int i, cx, cy;
	L = 1, insVal(L, 0, sx, sy);
	dx2 = sx-ex, dy2 = sy-ey;
	while(L > 0) {
		cx = Heap[1].x, cy = Heap[1].y;
		if(cx == ex && cy == ey)	break;
		delMin();
		Expand(cx+1, cy, cx, cy);
		Expand(cx-1, cy, cx, cy);
		Expand(cx, cy+1, cx, cy);
		Expand(cx, cy-1, cx, cy);
	}
	printf("%d\n", map[ex][ey]);
}
int main() {
	int n, t, row, x;
	int i, j;
	while(scanf("%d %d", &R, &C) == 2) {
		if(R == 0 && C == 0)	break;
		scanf("%d", &n);
		memset(map, 0, sizeof(map));
		for(i = 0; i < n; i++) {
			scanf("%d %d", &row, &t);
			while(t--) {
				scanf("%d", &x);
				map[row][x] = -1;
			}
		}		

		scanf("%d %d %d %d", &sx, &sy, &ex, &ey);		
		AStar();
	}
    return 0;
}
