#include <stdio.h>
#include <string.h>
int main() {
	char s1[200], s2[200];
	int Case = 0;
	while(gets(s1)) {
		if(strcmp(s1, "#") == 0)
			break;
		gets(s2);
		int LCS[102][102] = {};
		int i, j, l1 = strlen(s1), l2 = strlen(s2);
		for(i = 1; i <= l1; i++) {
			for(j = 1; j <= l2; j++) {
				if(s1[i-1] == s2[j-1]) {
					LCS[i][j] = LCS[i-1][j-1]+1;
				} else {
					LCS[i][j] = LCS[i-1][j] > LCS[i][j-1] ? 
						LCS[i-1][j] : LCS[i][j-1];
				}
			}
		}
		printf("Case #%d: you can visit at most %d cities.\n", ++Case, LCS[l1][l2]);
	}
    return 0;
}
