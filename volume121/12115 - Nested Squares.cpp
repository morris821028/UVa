#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
using namespace std;
char s[65536];
int main() {
//	freopen("in.txt", "r+t", stdin);
//	freopen("out1.txt", "w+t", stdout); 
	int testcase, cases = 0, n, q;
	scanf("%d", &testcase);
	while(testcase--) {
		scanf("%s %d", s, &q);
		n = strlen(s);
		printf("Square %d:\n", ++cases);
		int qcases = 0;
		while(q--) {
			int lx, ly, rx, ry;
			scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
			printf("Query %d:\n", ++qcases);
			for(int i = lx; i <= rx; i++) {
				for(int j = ly; j <= ry; j++) {
					int m = max(abs(i - n), abs(j - n));
					putchar(s[n - m - 1]);
				}
				puts("");
			}
		}
		puts("");
	}
	return 0;
}
/*
2
abca 2
3 2 5 7
3 2 3 2

Aacc32 1
1 1 8 2
*/
