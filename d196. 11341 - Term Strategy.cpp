#include<stdio.h>
main() {
	int T, n, m;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		int L[11][101] = {}, a, b, c;
		for(a = 1; a <= n; a++) 
			for(b = 1; b <= m; b++) 
				scanf("%d", &L[a][b]);
		int A[11][101] = {};/*A[a,b] 總共讀了 1~a 科，共花了 b 分鐘*/ 
		for(a = 1; a <= m; a++)	
			if(L[1][a] >=5) 
				A[1][a] = L[1][a];
		for(a = 2; a <= n; a++) {
			for(b = 1; b <= m; b++) { 
				int max = 0; 
				for(c = 1; c <= b; c++) /*花多久時間*/
					if(L[a][c] >= 5 && A[a-1][b-c]) { 
						if(max < L[a][c] + A[a-1][b-c]) {
							max = L[a][c] + A[a-1][b-c]; 
						} 
					}
				A[a][b] = max;
			} 
		} 
		if(A[n][m] == 0) 
			puts("Peter, you shouldn't have played billiard that much.");
		else 
			printf("Maximal possible average mark - %.2lf.\n", (double)A[n][m]/n + 1e-9);
	}
	printf("OLE\n"); 
	return 0;
}
