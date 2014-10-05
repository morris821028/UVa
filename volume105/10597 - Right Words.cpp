#include <stdio.h> 
#include <string.h>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	char s1[1024], s2[1024];
	while (scanf("%s", s1) == 1) {
		char start = s1[0];
		scanf("%*s %*s");
		set<char> re[128];
		set<char> rule[128][128];
		while (scanf("%s -> %s", s1, s2) == 2 && s1[0] != '#') {
			if (s2[1] == '\0')
				re[s2[0]].insert(s1[0]);
			else {
				rule[s2[0]][s2[1]].insert(s1[0]);
			}
		}
		while (scanf("%s", s1) == 1 && s1[0] != '#') {
			int n = strlen(s1);
			set<char> dp[64][64];
			for (int i = 0; i < n; i++) {
				dp[i][i].insert(re[s1[i]].begin(), re[s1[i]].end());
			}
			for (int i = 1; i < n; i++) {
				for (int j = 0; i + j < n; j++) {
					for (int k = j; k < i+j; k++) {
						for (set<char>::iterator a = dp[j][k].begin();
							a != dp[j][k].end(); a++)
						for (set<char>::iterator b = dp[k+1][i+j].begin();
							b != dp[k+1][i+j].end(); b++)
							dp[j][i+j].insert(rule[*a][*b].begin(), rule[*a][*b].end());
					}
				}
			}
			printf("%s is %sin L(G)\n", s1, dp[0][n-1].find(start) == dp[0][n-1].end() 
										? "not " : "");
		}
		puts("");
	}
	return 0;
}
/*
S
SABC
ab
S -> AB
S -> BC
A -> BA
A -> a
B -> CC
B -> b
C -> AB
C -> a
# -> #
baaba
ab
abaa
a
aaaaa
bbbbb
#
S
SAB
ab
S -> AB
A -> AA
A -> a
B -> b
# -> #
ab
aaab
aba
baaaaaaaa
abbbbbb
aaaaaba
baaaaaaaab
aaaa
a
ab
#
*/
