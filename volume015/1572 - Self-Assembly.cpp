#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;
int g[64][64];
int node(char a, char b) {
	return (a - 'A') + (b == '+' ? 0 : 26);
}
int rnode(char a, char b) {
	return (a - 'A') + (b == '+' ? 26 : 0);
}
int exist_cycle;
int main() {
	int n;
	char s[50];
	while(scanf("%d", &n) == 1) {
		memset(g, 0, sizeof(g));
		for(int i = 0; i < n; i++) {
			scanf("%s", s);
			for(int j = 0; j < 4; j++)	 {
				for(int k = 0; k < 4; k++) {
					if(j == k || s[2 * j] == '0' || s[2 * k] == '0')
						continue;
					int x = node(s[2 * j], s[2 * j + 1]);
					int y = rnode(s[2 * k], s[2 * k + 1]);
					g[x][y] = 1;
				}
			}
		}
		exist_cycle = 0;
		n = 52;
		for(int k = 0; k < n; k++) {
			for(int i = 0; i < n; i++)
				for(int j = 0; j < n; j++)
					g[i][j] |= g[i][k]&g[k][j];
		}
		for(int i = 0; i < n; i++)
			exist_cycle |= g[i][i];
		puts(exist_cycle ? "unbounded" : "bounded");
	}
	return 0;
}
/*
3
A+00A+A+ 00B+D+A- B-C+00C+
1
K+K-Q+Q-
*/
