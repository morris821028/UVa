#include<stdio.h>
#include<string.h>
int Max(int x, int y) {
	return x > y ? x : y; 
}
int main() {
	char s1[101], s2[101], s3[101];
	char DP[101][101][101], i, j, k;
	while(scanf("%s %s %s", s1, s2, s3) == 3) {
		memset(DP, 0, sizeof(DP));
		for(i = 0; s1[i]; i++)
			for(j = 0; s2[j]; j++)
				for(k = 0; s3[k]; k++) {
					if(s1[i] == s2[j] && s2[j] == s3[k])
						DP[i+1][j+1][k+1] = DP[i][j][k] + 1;
					else
						DP[i+1][j+1][k+1] = Max(Max(DP[i+1][j+1][k], DP[i+1][j][k+1]), DP[i][j+1][k+1]);
				}
		printf("%d\n", DP[i][j][k]);
	}
	return 0;
}
