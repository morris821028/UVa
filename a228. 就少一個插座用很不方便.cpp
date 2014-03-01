#include<stdio.h>
#include<string.h>
main() {
	int T, C = 0;
	int n, m, k, x;
	scanf("%d", &T);
	while(T--) {
		scanf("%d %d", &n, &m);
		long long DP[2][1<<12] ={};
		DP[0][0] = 1;
		int p, q, i, j, g = 1, h = 0;
		int tx, ty;
		for(i = 0; i < n; i++) {
			for(j  = 1; g = 1-g, h = 1-h, j <= m; j++) {
				scanf("%d", &x);
				for(k = 0; k < 1<<m<<1; k++) {
					p = 1 << j, q = p >> 1, tx = (k&p) != 0, ty = (k&q) != 0;
					if(x) {
                        DP[h][k] = DP[g][k^p^q];
						if(tx^ty)	DP[h][k] += DP[g][k];
					} else {
						DP[h][k] = tx | ty ? 0 : DP[g][k];
					}
				}
			}

			memset(DP[h], 0, sizeof(DP[h]));
			for(j = 0; j < (1<<m); j++)	DP[h][j<<1] = DP[g][j]%1000000007;
		}
		printf("Case %d: %d\n", ++C, DP[h][0]);
	}
	return 0;
}/*
1.凹角為11（橫豎都有插頭）：新狀態k'的這兩位均為0，因為兩個度用完了。
2.凹角為01（只有橫邊有插頭）：新狀態k'可以是10或01。
3.凹角為10（只有豎邊有插頭）：新狀態k'可以是10或01。
4.凹角為00（都沒插頭)：要么11，要么00。 （00的條件是此格為障礙）
*/
