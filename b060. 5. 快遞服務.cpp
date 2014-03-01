/**********************************************************************************/
/*  Problem: b060 "5. 快遞服務" from 95全國資訊學科能力決賽         */
/*  Language: C                                                                   */
/*  Result: AC (656ms, 760KB) on ZeroJudge                                        */
/*  Author: morris1028 at 2011-06-20 00:20:41                                     */
/**********************************************************************************/


#include<stdio.h>
#define Maxv 1000000 
int A[1001], Map[201][201];
int DP[201][201], Next[201][201];
void Update(int i, int j, int temp) {
	int t;
	if(i > j) t = i, i = j, j = t; 
	Next[i][j] = (Next[i][j] < temp) ? Next[i][j] : temp; 
} 
int DPstart(int n, int m) {
	int a, b, c;
	for(a = 1; a <= n; a++)
		for(b = a+1; b <= n; b++)
			DP[a][b] = Maxv;
	DP[1][2] = 0, A[0] = 3;
	for(a = 1; a <= m; a++) {
		if(A[a] == A[a-1])	continue;
		for(b = 1; b <= n; b++)/*init*/
			for(c = b+1; c <= n; c++)
				Next[b][c] = Maxv;
		for(b = 1; b <= n; b++)
			for(c = b+1; c <= n; c++) {
				if(DP[b][c] != Maxv) {
					Update(b, c, DP[b][c] + Map[A[a-1]][A[a]]);
					Update(A[a-1], b, DP[b][c] + Map[c][A[a]]);
					Update(A[a-1], c, DP[b][c] + Map[b][A[a]]);
				}
			}
		for(b = 1; b <= n; b++) 
			for(c = b+1; c <= n; c++) 
				DP[b][c] = Next[b][c];
	}
	int Min = Maxv;
	for(a = 1; a <= n; a++) 
		for(b = a+1; b <= n; b++) 
			Min = (Min < DP[a][b]) ? Min : DP[a][b];
	return Min; 
}
main() {
	int n, m, a, b, x;
	char c; 
	while(scanf("%d", &n) == 1) {
		for(a = 1; a <= n; a++)
			for(b = 1; b <= n; b++)
				scanf("%d", &Map[a][b]);
		m = 0;	
		while(scanf("%d%c", &x, &c) == 2 && c != '\n') {
			A[++m] = x;
		}
		A[++m] = x; 
		printf("%d\n", DPstart(n, m));
	}
	return 0;
}
