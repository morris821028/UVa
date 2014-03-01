#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define oo 214748367
int DP[101][101][3] = {};
int Min(int x, int y) {
	return x < y ? x : y;
}
int Max(int x, int y) {
	return x > y ? x : y;
}
int main() {
	int n, p, i, j, k;
	int W[100], Dis[100];
	while(scanf("%d %d", &n, &p) == 2) {
		if(n == 0 && p == 0)
			break;
		for(i = 0; i < n; i++)
			scanf("%d", &W[i]);
		for(i = 0; i < n-1; i++)
			scanf("%d", &Dis[i]);

		int min = 2147483647;
		int Sum[101] = {};		
		int choose[101][101] = {};
		int length, tlength;
		Sum[n-1] = W[n-1];
		for(i = n-2; i >= 0; i--)
			Sum[i] = Sum[i+1] + W[i];
		for(i = 0; i < n; i++) {
			choose[i][i+1] = 0;
			for(j = i+2; j < n; j++) {
				length = 0;
				for(k = i; k < j; k++)
					length += Dis[k];
				length = length /2;
				tlength = 0;
				choose[i][j] = 0;
				for(k = j; k > i; k--) {
					choose[i][j] += W[k];
					if(tlength > length)	break;
					tlength += Dis[k-1];
				}
			}
		}
		memset(DP, 0, sizeof(DP));
		for(i = 0; i < p; i++) {
			for(k = 0; k < n; k++) {
				if(i == 0) {
					DP[i][k][0] = oo;
					DP[i][k][1] = Sum[0];
					DP[i][k][2] = 0;
					continue;
				}
				DP[i][k][0] = oo;
				DP[i][k][1] = oo;
				DP[i][k][2] = oo;
				for(j = 0; j < k; j++) {
					int cost1, cost2, cost3;
					cost1 = choose[j][k] + Sum[k];
					if(i != 0)
						cost2 = Min(DP[i-1][j][0], DP[i-1][j][1]);
					else
						cost2 = oo;
					if(cost1 >= cost2) {
						if(cost1 <= DP[i][k][1]) {
							DP[i][k][1] = cost1;
							if(cost2 < DP[i][k][2])
								DP[i][k][2] = cost2;
						}
					} else {
						DP[i][k][0] = Min(cost2, DP[i][k][0]);
					}
					
					cost2 = DP[i-1][j][1] - cost1;
					if(i != 0) {
						cost3 = DP[i-1][j][2];
					} else
						cost3 = oo;
					if(cost1 >= cost2 && cost1 >= cost3) {
						if(cost1 <= DP[i][k][1]) {
							DP[i][k][1] = cost1;
							if(Min(DP[i][k][2], Max(cost2, cost3)) < DP[i][k][2])
								DP[i][k][2] = Min(DP[i][k][2], Max(cost2, cost3));
						}
					} else {
						DP[i][k][0] = Min(DP[i][k][0], Max(cost2, cost3));
					}
				}
			}
		}
		for(i = p-1; i < n; i++) {
			if(DP[p-1][i][0] < min)
				min = DP[p-1][i][0];
			if(Max(DP[p-1][i][1], DP[p-1][i][2]) < min)
				min = Max(DP[p-1][i][1], DP[p-1][i][2]);
		}
		printf("%d\n", min);
	}
    return 0;
}/*
5 2
100
20
30
100
50
5
1
2
10

8 3
30
60
10
30
30
40
50
50

100
200
10
20
40
1
2
*/
