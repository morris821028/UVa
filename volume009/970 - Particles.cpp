#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

int main() {
	int testcase;
	int table[3][3] = {{1,0,2},{0,1,1},{2,1,0}};
	char s[1024];
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s", s);
		int dp[128][128][3] = {}, n = strlen(s);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j + i < n; j++) {
				for(int k = j; k < j + i; k++) {
					for(int p = 0; p < 3; p++) {
						if(dp[j][k][p])
						for(int q = 0; q < 3; q++) {
							if(dp[k+1][j+i][q]) {
								dp[j][j+i][table[p][q]] = 1;
							}
						}
					}
					if(dp[j][j+i][0] && dp[j][j+i][1] && dp[j][j+i][2])
						break;
				}
				if(i == 0)
					dp[j][j][s[j]-'X'] = 1;
			}
		}
		for(int i = 2; i >= 0; i--) {
			if(dp[0][n-1][i]) {
				printf("%c\n", i+'X');
				break;
			}
		}
	}
	return 0;
}
/*
1
ZYX
*/
