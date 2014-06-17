#include<stdio.h>
struct Link {
    int x, y;
	long long v;
}Data[10001], X[10001];
void Merge(int l, int m, int h) {
    int In1 = l, In2 = m+1;
    int a, b, Top = 0;
    while(In1 <= m && In2 <= h) {
        if(Data[In1].v < Data[In2].v)
            X[Top++] = Data[In1++];
        else
            X[Top++] = Data[In2++];
    }
    while(In1 <= m) X[Top++] = Data[In1++];
    while(In2 <= h)    X[Top++] = Data[In2++];
    for(a = 0, b = l; a < Top; a++, b++)
        Data[b] = X[a];
}
void MergeSort(int l, int h) {
    if(l < h) {
        int m = (l+h)/2;
        MergeSort(l, m);
        MergeSort(m+1, h);
        Merge(l, m, h);
    }
}
long long DP[101][101], MinV = -2147483647;
main() {
	MinV = MinV;
	int n, k, a, b, c, d;
	long long map[101][101];
	int D[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
	while(scanf("%d %d", &n, &k) == 2) {
		for(a = 0, c = 0; a < n; a++)
			for(b = 0; b < n; b++) {
				scanf("%lld", &map[a][b]);
				Data[c].x = a, Data[c].y = b, Data[c++].v = map[a][b];
				DP[a][b] = MinV;
			}
		MergeSort(0, n*n-1);
		DP[0][0] = map[0][0];
		int x, y, tx, ty, d;
		long long v, tv;
		long long Ans = map[0][0], tmp;
		for(a = 0; a < n*n; a++) {
			for(b = 0; b < 4; b++) {
				x = Data[a].x, y = Data[a].y, v = map[x][y];
				for(c = 1; c <= k; c++) {
					tx = x+D[b][0]*c, ty = y+D[b][1]*c;
					if(tx >= 0 && tx < n &&	 ty >= 0 && ty < n && v < map[tx][ty]) {
						tv = map[tx][ty];
						if(DP[x][y] == MinV) continue;
						tmp = DP[x][y] + tv;
						if(DP[tx][ty] < tmp) {
							DP[tx][ty] = tmp;
							Ans = Ans > tmp ? Ans : tmp;
						}
					}
				}
			}
		}
		printf("%lld\n", Ans);
	}
	return 0;
}
