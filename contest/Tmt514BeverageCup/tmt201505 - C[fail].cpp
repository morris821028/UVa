#include <stdio.h>
#include <string.h>
#include <algorithm>
using namespace std;

const int MAXN = 128;
int A[MAXN][MAXN], n, m;
int S[MAXN][MAXN];
void print() {
	for (int i = 1; i <= n; i++, puts(""))
		for (int j = 1; j <= m; j++)
			printf("%2d", A[i][j]);
	puts("");
}
int countArea(int lx, int ly, int rx, int ry) {
	return S[rx][ry] - S[lx-1][ry] - S[rx][ly-1] + S[lx-1][ly-1];
}
int isOpenOnly(int x, int y) {
	if (x < 0 || y < 0 || x > n || y > m)
		return 0;
	if (A[x][y])	
		return 0;
	int v1 = countArea(x, 1, x, y) + countArea(1, y, x, y);
	int v2 = countArea(x, y, n, y) + countArea(x, y, x, m);
	if (v1 == 0 && v2 > 0)
		return 1;
	return 0;
}
int isInnerEmpty(int x, int y) {
	if (x < 0 || y < 0 || x > n || y > m)
		return 0;
	if (A[x][y])	
		return 0;
	int v1 = countArea(x, 1, x, y) + countArea(1, y, x, y);
	int v2 = countArea(x, y, n, y) + countArea(x, y, x, m);
	if (v1 == 0 && v2 == 0) {
		printf("inner empty %d %d\n", x, y);
		return 1;
	}
	return 0;
}
 
int rule1() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (A[i][j])
				continue;
			if (isInnerEmpty(i, j)) { // inner empty cell
				if (A[i+1][j] == 0 && A[i][j+1] == 0) 
					continue;
				if (A[i+1][j] && (A[i][j+1] == 0 || (A[i][j+1] < A[i+1][j])))
					swap(A[i][j], A[i+1][j]);
				else
					swap(A[i][j], A[i][j+1]);
				return 1;
			}
		}
	}
	return 0;
}
int rule2() {
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= m; j++) {
			if (A[i][j])
				continue;
			if (isOpenOnly(i, j) && !isOpenOnly(i+1, j) && !isOpenOnly(i, j+1)) {
				if (A[i+1][j]) {
					int t = A[1][j];
					for (int k = 2; k <= n; k++)
						A[k-1][j] = A[k][j];
					A[n][j] = t;
					return 1;
				}
				if (A[i][j+1]) {
					int t = A[i][1];
					for (int k = 2; k <= m; k++)
						A[i][k-1] = A[i][k];
					A[i][m] = t;
					return 1;
				}
			}
		}
	}
	return 0;
}
void simulate() {
	while (true) {
		print();
		for (int i = 1; i <= n; i++) {
			int sum = 0;
			for (int j = 1; j <= m; j++) {
				sum += A[i][j] > 0;
				S[i][j] = S[i-1][j] + sum;
			}
		}
		
		if (rule1())
			continue;
		if (rule2())
			continue;
		break; 
	}
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d %d", &n, &m);
		memset(A, 0, sizeof(A));
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				scanf("%d", &A[i][j]);
		simulate();
	}
	return 0;
}
/*
3
3 3
0 0 1
0 2 0
3 0 0
6 6
0 0 0 0 0 4
0 0 0 0 1 0
0 0 0 3 0 0
0 0 5 0 0 0
0 6 0 0 0 0
2 0 0 0 0 0
3 5
1 2 3 4 5
6 7 0 0 0
8 0 0 0 0
*/
