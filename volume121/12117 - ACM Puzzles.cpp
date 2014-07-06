#include <stdio.h>
#include <algorithm>
using namespace std; 
char puzzles[22][3][4] = {
	{"*  ", "*  ", "*  "},
	{"*  ", "** ", "*  "},
	{"** ", " * ", "** "},
	{" * ", "** ", "** "},
	{" * ", "***", " * "},
	{"** ", "*  ", "** "},
	//
	{" * ", "** ", " * "},
	{"  *", " **", "** "},
	{"** ", " **", "  *"},
	{" * ", "** ", "*  "},
	{"*  ", "** ", " * "},
	{"** ", "** ", "*  "},
	// 
	{"** ", "** ", " * "},
	{"** ", "*  ", "*  "},
	{"** ", " * ", " * "},
	{" **", "** ", "*  "},
	{"*  ", "** ", " **"},
	{"*  ", "*  ", "** "},
	//
	{" * ", " * ", "** "},
	{"***", " * ", " * "},
	{" * ", " * ", "***"},
	{"*  ", "** ", "** "}
};

const long long mod = 1000000000000LL;
long long dp[2048][3][3][3] = {};
int main() {
	dp[0][0][0][0] = 1;
	for(int i = 0; i <= 2000; i++) {
		for(int p = 0; p < 3; p++)
		for(int q = 0; q < 3; q++)
		for(int r = 0; r < 3; r++) {	
			for(int j = 0; j < 22; j++) {
				if(puzzles[j][0][p] != '*' ||
					puzzles[j][1][q] != '*' ||
					puzzles[j][2][r] != '*')
						continue;
				if(p && puzzles[j][0][p-1] != ' ')
					continue;
				if(q && puzzles[j][1][q-1] != ' ')
					continue;
				if(r && puzzles[j][2][r-1] != ' ')
					continue;
				// match
				int r1, r2, r3;
				r1 = i+p, r2 = i+q, r3 = i+r;
				for(int k = 0; k < 3; k++) {
					if(puzzles[j][0][k] == '*')
						r1++;
					if(puzzles[j][1][k] == '*')
						r2++;
					if(puzzles[j][2][k] == '*')
						r3++;
				}
				int mm = min(min(r1, r2), r3);
				dp[mm][r1-mm][r2-mm][r3-mm] += dp[i][p][q][r];
				if(dp[mm][r1-mm][r2-mm][r3-mm] >= mod)
					dp[mm][r1-mm][r2-mm][r3-mm] %= mod;
			}
		}
	}
	int n, cases = 0;
	while(scanf("%d", &n) == 1 && n)
		printf("Case %d: %lld\n", ++cases, dp[n][0][0][0]);
	return 0;
}
