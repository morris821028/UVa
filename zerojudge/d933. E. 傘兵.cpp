#include<stdio.h>
struct Queue {
	int x, y;
}Q[10001];
struct coordinate{
	int t, x, y;
}set[1001], X[1001];
void Merge(int l, int m, int h) {
    int In1 = l, In2 = m+1;
    int a, b, Top=0;
    while(In1 <= m && In2 <= h) 
        if(set[In1].t < set[In2].t)
             X[Top++] = set[In1++];
       else  X[Top++] = set[In2++];
    while(In1 <= m)   X[Top++] = set[In1++];
    while(In2 <= h)   X[Top++] = set[In2++];
    for(a = 0, b = l; a < Top; a++, b++) 
        set[b] = X[a];
} 
void MergeSort(int l, int h) {
    if(l < h) {
        int m = (l+h)/2;
        MergeSort(l  , m);
        MergeSort(m+1, h);
        Merge(l, m, h); 
    }
}
main() {
	int T, R, C, N, r, c, v, a, b;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d %d", &R, &C, &N);
		int Map[101][101];
		
		for(a = 0; a < N; a++) {
			scanf("%d %d %d", &r, &c, &v);
			Map[r][c] = v;
			set[a].t = v, set[a].x = r, set[a].y = c;
		}
		MergeSort(0, N-1);
		
		int Qt = 0, Used[101][101] = {}, tx, ty, ins = 1;
		Q[0].x = set[0].x, Q[0].y = set[0].y, Used[Q[0].x][Q[0].y] = 1;
		for(a = 0; a <= Qt; a++) {
			tx = Q[a].x, ty = Q[a].y;
			while(ins < N && Map[tx][ty] == set[ins].t) {
				Q[++Qt].x = set[ins].x, Q[Qt].y = set[ins++].y;
				Used[Q[Qt].x][Q[Qt].y] = 1;
			}
			
			if(tx+1<= R && Used[tx+1][ty] == 0) {
				Used[tx+1][ty] = 1;
				Map[tx+1][ty] = Map[tx][ty]+1;
				Q[++Qt].x = tx+1, Q[Qt].y = ty;
			}
			if(ty+1<= C && Used[tx][ty+1] == 0) {
				Used[tx][ty+1] = 1;
				Map[tx][ty+1] = Map[tx][ty]+1;
				Q[++Qt].x = tx, Q[Qt].y = ty+1;
			}
			if(tx-1>=1 && Used[tx-1][ty] == 0) {
				Used[tx-1][ty] = 1;
				Map[tx-1][ty] = Map[tx][ty]+1;
				Q[++Qt].x = tx-1, Q[Qt].y = ty;
			}
			if(ty-1>=1 && Used[tx][ty-1] == 0) {
				Used[tx][ty-1] = 1;
				Map[tx][ty-1] = Map[tx][ty]+1;
				Q[++Qt].x = tx, Q[Qt].y = ty-1;
			}
		}
		for(a = 1; a <= R; puts(""), a++)
			for(b = 1; b <= C; b++)
				printf("%d ", Map[a][b]);
	}
	return 0;
}
