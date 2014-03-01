#include<stdio.h>
main() {
	int N1, N2, a, b, s1[102], s2[102], C = 0;
	while(scanf("%d %d", &N1, &N2) == 2) {
		if(N1 + N2 == 0) break;
		for(a = 1; a <= N1; a++) 
			scanf("%d", &s1[a]);
		for(a = 1; a <= N2; a++)
			scanf("%d", &s2[a]);
		int LCS[102][102] = {};
		for(a = 1; a <= N1; a++)
			for(b = 1; b <=N2; b++)
				if(s1[a] == s2[b])
					LCS[a][b] = LCS[a-1][b-1] + 1;
				else
					LCS[a][b] = (LCS[a-1][b] > LCS[a][b-1])? LCS[a-1][b] : LCS[a][b-1];
		printf("Twin Towers #%d\n", ++C);
		printf("Number of Tiles : %d\n\n", LCS[N1][N2]);
	}
	return 0;
}
