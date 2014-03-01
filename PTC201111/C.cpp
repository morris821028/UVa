#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
char map[1001][15][15], pst[1001][15];
int main() {
	int d, s;
	int mapmi[1001], mapni[1001];
	int i, j, k;
	while(scanf("%d %d", &d, &s) == 2) {
		for(i = 0; i < d; i++) {
			while(scanf("%d %d", &mapmi[i], &mapni[i]) == 2)
				break;
			for(j = 0; j < mapni[i]; j++) {
				while(scanf("%s", map[i][j]) == 1)
					break;
			}
		}
		for(i = 0; i < s; i++) {
			while(scanf("%s", pst[i]) == 1)
				break;
		}
		int DP[1001];
		DP[0] = 1;
		for(i = 1; i <= s; i++) {
			DP[i] = DP[i-1];
			for(j = 0; j < d; j++) {
				if(i - mapni[j] < 0)	continue;
				for(k = 0; k < mapni[j]; k++)
					if(strcmp(pst[i-mapni[j]+k], map[j][k]))
						break;
				if(k == mapni[j]) {
					DP[i] += DP[i-mapni[j]]*mapmi[j];
					DP[i] %= 65535;
				}
			}
		}
		printf("%d\n", DP[s]);
	}
	return 0;
}
/*
1 2
1 2 a b
a b
*/
