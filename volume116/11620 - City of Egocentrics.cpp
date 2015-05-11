#include <stdio.h> 
#include <algorithm>
using namespace std;

const int MAXN = 128;
int A[MAXN][MAXN], B[MAXN][MAXN], n;
int mark[MAXN][MAXN];
void print(char c) {
	printf("%c\n", c);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			if (mark[i][j])
				printf("%d %d\n", i, j);
	}
}
void solve() {
	for (int i = 0; i < n; i++) {
		int sum = 0, l, r;
		for (int j = 0; j < n; j++)
			sum += A[i][j];
		l = 0, r = sum;
		for (int j = 0; j < n; j++) {
			r -= A[i][j];
			mark[i][j] = (l == r);
			l += A[i][j];
		}
	}
	print('H');
	
	for (int i = 0; i < n; i++) {
		int sum = 0, l, r;
		for (int j = 0; j < n; j++)
			sum += A[j][i];
		l = 0, r = sum;
		for (int j = 0; j < n; j++) {
			r -= A[j][i];
			mark[j][i] = (l == r);
			l += A[j][i];
		}
	}
	print('V');
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i-1 >= 0 && j-1 >= 0)
				B[i][j] = B[i-1][j-1] + A[i][j];
			else
				B[i][j] = A[i][j];
		}
	} 
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int l = 0, r = 0;
			if (i-1 >= 0 && j-1 >= 0)
				l = B[i-1][j-1];
			int ex, ey;
			ex = i + min(n-1-i, n-1-j), ey = j + min(n-1-i, n-1-j);
			r = B[ex][ey] - l - A[i][j];
			mark[i][j] = (l == r);
		}
	}
	print('D');
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i-1 >= 0 && j+1 < n)
				B[i][j] = B[i-1][j+1] + A[i][j];
			else
				B[i][j] = A[i][j];
		}
	} 
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int l = 0, r = 0;
			if (i-1 >= 0 && j+1 < n)
				l = B[i-1][j+1];
			int ex, ey;
			ex = i + min(n-1-i, j), ey = j - min(n-1-i, j);
			r = B[ex][ey] - l - A[i][j];
			mark[i][j] = (l == r);
		}
	}
	print('A');
}
int main() {
	int testcase;
	scanf("%d", &testcase);
	while (testcase--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &A[i][j]);
		
		solve();
	}
	return 0;
}
/*
3
3
1 2 3
4 5 6
7 8 9
3
1 1 1
1 1 1
1 1 1
4
5 7 7 6
2 4 0 8
6 1 0 7
6 8 7 5
*/
