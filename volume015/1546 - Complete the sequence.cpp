#include <bits/stdc++.h> 
using namespace std;

const int MAXN = 105;
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		int n, m;
		scanf("%d %d", &n, &m);
		int a[MAXN][MAXN] = {};
		for (int i = 0; i < n; i++)
			scanf("%d", &a[0][i]);
			
		for (int i = 1; i < n; i++) {
			for (int j = i; j < n; j++)
				a[i][j] = a[i-1][j] - a[i-1][j-1];
		}
		
		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				printf("%2d ", a[i][j]);
			puts("");
		}
		*/
		
		for (int i = n-1; i >= 0; i--) {
			for (int j = n; j < (n+m); j++)
				a[i][j] = a[i+1][j] + a[i][j-1];
		}
		
		/*
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n+m; j++)
				printf("%2d ", a[i][j]);
			puts("");
		}
		*/
		
		for (int i = n; i < (n+m); i++)
			printf("%d%c", a[0][i], " \n"[i==n+m-1]);
	}
	return 0;
}
/*
4
6  3
1  2  3  4  5  6
8  2
1  2  4  7  11  16  22  29
10  2
1  1  1  1  1  1  1  1  1  2
1  10
3
*/
