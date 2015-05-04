// floyd
#include <stdio.h> 
#include <algorithm>
using namespace std;

const int MAXN = 128;
int f[MAXN][MAXN];
int anti_floyd(int n) {
	int adj[MAXN][MAXN] = {};
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj[i][j] = 1;
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (f[i][k] + f[k][j] < f[i][j]) {
					puts("Need better measurements.");
					return 0;
				}
				if (i == j || i == k || j == k)
					continue;
				if (f[i][k] + f[k][j] == f[i][j])
					adj[i][j] = 0;
			}
		}
	}
	
	int e = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (i == j)	continue;
			e += adj[i][j];
		}
	}
	
	printf("%d\n", e);
	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++)
			if (adj[i][j])
				printf("%d %d %d\n", i+1, j+1, f[i][j]);
	}
	return 1;
}
int main() {
	int testcase, cases = 0, n;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < i; j++)
				scanf("%d", &f[i][j]), f[j][i] = f[i][j];
			f[i][i] = 0;
		}
		
		printf("Case #%d:\n", ++cases);
		int valid = anti_floyd(n);
		puts("");
	}
	return 0;
}
