#include <stdio.h>
#include <string.h>
char A[1001], B[1001];
short LCS[1001][1001];
int main() {
	int i, j;
	while(gets(A)) {
		gets(B);
		memset(LCS, 0, sizeof(LCS));
		int la = strlen(A), lb = strlen(B);
		for(i = 1; i <= la; i++) {
			for(j = 1; j <= lb; j++) {
				if(A[i-1] == B[j-1])
					LCS[i][j] = LCS[i-1][j-1]+1;
				else
					LCS[i][j] = LCS[i][j-1] > LCS[i-1][j] ?	LCS[i][j-1] : LCS[i-1][j];
			}
		}
		printf("%d\n", LCS[la][lb]);
	}
    return 0;
}
