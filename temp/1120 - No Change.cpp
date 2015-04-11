#include <stdio.h> 
#include <string.h>
using namespace std;
#define MAXL (100000>>5)+1
#define GET(x) (mark[(x)>>5]>>((x)&31)&1)
#define SET(x) (mark[(x)>>5] |= 1<<((x)&31))
int mark[MAXL];
int main() {
	int testcase, n, m, A[10];
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		for (int i = 0; i < m; i++) {
			scanf("%d", &A[i]);
		}
		
		for (int i = 1; i < m; i++)
			A[i] += A[i-1];
		
		memset(mark, 0, sizeof(mark));
		SET(0);
		for (int i = 0; i < m; i++) {
			for (int j = 0; j + A[i] <= n; j++) {
				if (GET(j))
					SET(j + A[i]);
			}
		}
		puts(GET(n) ? "YES" : "NO");
		if (testcase)
			puts("");
	}
	return 0;
}
/*
1
13 3 9 2 1
*/
