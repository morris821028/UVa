#include <stdio.h> 
#include <algorithm>
using namespace std;
int f[10][10] = {
	{0},
	{0},
	{2, 1, 0},
	{2, 1, 3, 1, 0},
	{2, 3, 3, 1, 0},
	{2, 3, 3, 1, 5, 1, 0},
	{2, 4, 3, 2, 5, 1, 0},
	{2, 4, 3, 2, 5, 1, 7, 1, 0},
	{2, 7, 3, 2, 5, 1, 7, 1, 0},
	{2, 7, 3, 4, 5, 1, 7, 1, 0}
};
int main() {
	int n, m, x;
	while (scanf("%d %d", &n, &m) == 2 && n + m) {
		int A[10] = {};
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			for(int j = 0; f[x][j]; j += 2) {
				A[f[x][j]] += f[x][j + 1];
			}
		}
		for (int i = 0; i < m; i++) {
			scanf("%d", &x);
			for(int j = 0; f[x][j]; j += 2) {
				A[f[x][j]] -= f[x][j + 1];
			}
		}
		int ret = 1;
		for (int i = 0; i < 10; i++)
			ret &= A[i] == 0;
		puts(ret ? "YES" : "NO");
	}
	return 0;
}
/*
1 1
9
9
1 2
5
3 6
0 0
*/
