#include <bits/stdc++.h> 
using namespace std;

// O(n^4)

const int MAXN = 80;

int row[MAXN], col[MAXN];

int place(int x, int y, int row[], int col[], int n, int m) {
	static int sx[MAXN], sy[MAXN];
	memcpy(sx, row, sizeof(sx[0])*n);
	memcpy(sy, col, sizeof(sy[0])*m);
	for (int i = x; i < n; i++) {
		static int16_t C[MAXN+1], A[MAXN];
		int An = 0;
		memset(C, 0, sizeof(C[0])*(n+1));
		for (int j = y; j < m; j++) {
			if (sy[j] > 0)
				C[sy[j]]++, An++;
		}
		for (int j = n-1; j > 0; j--)
			C[j] += C[j+1];
		for (int j = y; j < m; j++) {
			if (sy[j] > 0)
				A[--C[sy[j]]] = j;
		} 
		
		for (int j = 0; sx[i] > 0 && j < An; j++) {
			sx[i]--;
			sy[A[j]]--;
		}
		
		if (sx[i])
			return 0;
		y = 0;
	}
	
	for (int i = 0; i < m; i++) {
		if (sy[i])
			return 0;
	}
	
	return 1;
}

int main() {
	int n, m;
	int cases = 0;
	while (scanf("%d %d", &n, &m) == 2 && n) {
		for (int i = 0; i < n; i++)
			scanf("%d", &row[i]);
		for (int i = 0; i < m; i++)
			scanf("%d", &col[i]);
						
		int ret = 0;
		for (int i = 0; i < n; i++) {
			if (row[i] > m)
				goto DONE;
		}
		for (int i = 0; i < m; i++) {
			if (col[i] > n)
				goto DONE;
		}
		
		ret = place(0, 0, row, col, n, m);
		
		if (!ret)
			goto DONE;
		
		static char sol[MAXN][MAXN+1];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int f = place(i + (j==m-1), (j+1)%m, row, col, n, m);
				if (!f) {
					sol[i][j] = 'Y';
					row[i]--, col[j]--;
				} else {
					sol[i][j] = 'N';
				}
			}
		} 
		
	
		DONE:	
		if (cases++)
			puts("");
		if (!ret) {
			puts("Impossible");
		} else {
			for (int i = 0; i < n; i++) {
				sol[i][m] = '\0';
				puts(sol[i]);
			}
		}
	}
	return 0;
}
/*
2 2
1 2
1 1

3 3
2 1 2
1 2 2

3 5
3 3 1
3 1 1 0 2

0 0
*/
