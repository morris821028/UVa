#include<stdio.h>
typedef struct {
	int x, y;
}Link;
Link Next[50001], Pre[50001], X[50001];
int A[10001], DP[10001];
int Sn[10001], Cn[10001], pres[10001], prec[10001];
void MergeSort(int , int, Link[]);
void Merge(int , int , int, Link[]);
int Backtracking(int n) {
	int a, b, c, tn, Max = -1;
	int Queue[10001], Qt = -1, Used[10001] = {};
	for(a = 1; a <= n; a++)
		Max = (Max > DP[a]) ? Max : DP[a];
	for(a = 1; a <= n; a++)
		if(DP[a] == Max)
			Queue[++Qt] = a, Used[a] = 1;
	for(a = 0; a <= Qt; a++) {
		tn = Queue[a];
		for(b = 0, c = pres[tn]; b < prec[tn]; b++, c++)
			if(DP[tn] == A[tn] + DP[Pre[c].y]) {
				if(Used[Pre[c].y] == 0) {
					Used[Pre[c].y] = 1;
					Queue[++Qt] = Pre[c].y;
				}
			}
	}
	return Qt+1;
}
int	BFS_DP(int n) {
	int a, b, c, tn;
	int Queue[20001], Qt = -1, Used[10001] = {};
	for(a = 1; a <= n; a++) {
		DP[a] = -1;
		if(prec[a] == 0)
			Queue[++Qt] = a, Used[a] = 1, DP[a] = A[a];
	}
	for(a = 0; a <= Qt; a++) {
		tn = Queue[a];
		for(b = 0, c = Sn[tn]; b < Cn[tn]; b++, c++)
			if(DP[Next[c].y] < A[Next[c].y] + DP[tn]) {
				DP[Next[c].y] = A[Next[c].y] + DP[tn];
				if(Used[Next[c].y] == 0) {
					Used[Next[c].y] = 1;
					Queue[++Qt] = Next[c].y;
				}
			}
		Used[tn] = 0;
	}
	return Backtracking(n);
}
main() {
	int n, m, a, C = 0;
	while(scanf("%d %d", &n, &m) == 2) {
		for(a = 1; a <= n; a++)
			scanf("%d", &A[a]);
		for(a = 0; a < m; a++) {
			scanf("%d %d", &Next[a].x, &Next[a].y);
			Pre[a].x = Next[a].y;
			Pre[a].y = Next[a].x;
		}
		for(a = 1; a <= n; a++)
			Sn[a] = -1, Cn[a] = 0, pres[a] = -1, prec[a] = 0;
		MergeSort(0, m-1, Next);
		MergeSort(0, m-1, Pre);
		for(a = 0; a < m; a++) {
			if(Sn[Next[a].x] == -1)
				Sn[Next[a].x] = a;
			Cn[Next[a].x] ++;
		}
		for(a = 0; a < m; a++) {
			if(pres[Pre[a].x] == -1)
				pres[Pre[a].x] = a;
			prec[Pre[a].x] ++;
		}
		printf("%d\n", BFS_DP(n));
	}
	return 0;
}
void Merge(int l, int m, int h, Link Data[]) {
	int In1 = l, In2 = m+1;
	int a, b, Top = 0;
	while(In1 <= m && In2 <= h)
		if(Data[In1].x < Data[In2].x)
			X[Top++] = Data[In1++];
		else X[Top++] = Data[In2++];
	while(In1 <= m)	X[Top++] = Data[In1++];
	while(In2 <= h) X[Top++] = Data[In2++];
	 
	for(a = 0, b = l; a < Top; a++, b++)
		Data[b] = X[a];
}
void MergeSort(int l, int h, Link Data[]) {
	if(l < h) {
		int m = (l+h)/2;
		MergeSort(l, m, Data);
		MergeSort(m+1, h, Data);
		Merge(l, m, h, Data);
	}
}
