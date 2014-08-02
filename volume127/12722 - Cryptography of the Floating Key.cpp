#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;
char s[2048];
int g[512][512];
void show(int n, int m) {
	for(int i = 0; i < n; i++, puts(""))
		for(int j = 0; j < m; j++)
			printf("%c", g[i][j]);
}
int main() {
	int testcase, cases = 0, n, m;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s %d %d", s, &n, &m);
		int len = strlen(s);
		while(n * m < len) {
			if(n == m)	m <<= 1;
			else if(n < m)	n += m;
			else		m += n;
		}
		n = len / m + 1;
		int blank = n * m - len;
		for(int i = m-1, k = 0; i >= 0; i--) {
			for(int j = 0; j < n; j++) {
				if(k < len) {
					if(j == n-1 && blank)
						g[j][i] = ' ', blank--;
					else
						g[j][i] = (int)s[k++];
				} else
					g[j][i] = ' ';
			}
		}
		for(int i = 0, color = 0, x = 0, y = 0; i < n-1; i++) {
			if(g[i+1][0] == ' ')	break;
			int st = i%2 ? m-1 : 0;
			int dy = i%2 ? -1: 1; 
			for(int j = st; j >= 0 && j < m; j += dy) {
				if(color % 2 == 0) {
					x = i, y = j;
				} else {
					swap(g[x][y], g[i][j]);
				}
				color++;
			}
		}
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(g[i][j] >= 'a' && g[i][j] <= 'z') {
					g[i][j] = (g[i][j]-'a' - (i + j + 2) + 2600)%26 + 'a';
				}
			}
		}		

		printf("Case #%d: ", ++cases);
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {
				if(g[i][j] == ' ')	continue;
				printf("%c", g[i][j]);
			}
		}
		puts("");
	}
	return 0;
}
/*
3
zsvmvjfnroqfdek 3 3
vnvxjbxylndjhzq 1 1
uhyeobnqcmayftjvtttrplnraykamqw 50 100

10
gyytetorcanweobhsxhykgumsicihuospggbdicrmmhxdhzfzpmh 15 13
*/
