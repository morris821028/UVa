#include <bits/stdc++.h> 
using namespace std;
class XOR_GAUSSIAN { // XOR Gaussian Elimination
public:
    static const int MAXN = 700;
    char mtx[MAXN][MAXN+1], varX[MAXN];
    int n;
    void compute() {
    	int row = 0, col = 0, arb = 0;
    	int equ = n, var = n;
    	while (row < equ && col < var) {
    		int c = row;
    		for (int i = row; i < equ; i++)
    			if (mtx[i][col])
    				c = i;
    		for (int i = 0; i <= var; i++)
                swap(mtx[c][i], mtx[row][i]);
    		if (mtx[row][col] == 0) {
    			col++, arb++;
    			continue;
    		}    		
    		for (int i = 0; i < equ; i++) {
    			if (i == row || mtx[i][col] == 0) continue;
    			for (int j = var; j >= 0; j--)
    				mtx[i][j] ^= mtx[row][j];
    		}
    		row++, col++;
    	}
    	memset(varX, 0, sizeof(varX));
    	for (int i = 0, j; i < equ; i++) {
    		if (mtx[i][var] == 0)
    			continue;
    		for (j = 0; j < var && mtx[i][j] == 0; j++);
    		varX[j] = mtx[i][var];
    	}
    }
    void init(int n) {
    	this->n = n;
    	for (int i = 0; i < n; i++)
    		for (int j = 0; j <= n; j++)
    			mtx[i][j] = 0;
    }
} gauss;
int main() {
	int n, m, d;
	int g[32][32];
	int cases = 0;
	while (scanf("%d %d %d", &m, &n, &d) == 3 && n) {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				scanf("%d", &g[i][j]);
		int N = n*m;
		gauss.init(N);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int x = i*m + j, tx, ty;
				gauss.mtx[x][N] = g[i][j];
				gauss.mtx[x][x] = 1;
				for (int dx = -d; dx <= d; dx++) {
					int v = d - abs(dx);
					int dy[2] = {-v, v}, dn = v == 0 ? 1 : 2;
					for (int k = 0; k < dn; k++) {
						tx = i + dx, ty = j + dy[k];
						if (tx < 0 || ty < 0 || tx >= n || ty >= m)
							continue;
						gauss.mtx[x][tx*m+ty] = 1;
					}
				}
			}
		}
		gauss.compute();
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				if (gauss.varX[i*m+j] == 0)
					continue;
				g[i][j] ^= 1;
				int tx, ty;
				for (int dx = -d; dx <= d; dx++) {
					int v = d - abs(dx);
					int dy[2] = {-v, v}, dn = v == 0 ? 1 : 2;
					for (int k = 0; k < dn; k++) {
						tx = i + dx, ty = j + dy[k];
						if (tx < 0 || ty < 0 || tx >= n || ty >= m)
							continue;
						g[tx][ty] ^= 1;
					}
				}
			}
		}
		
		int ok = 1;
		for (int i = 0; i < n; i++)  {
			for (int j = 0; j < m; j++) { 
				ok &= g[i][j] == 0;
			}
		}
		printf("%d\n", ok);
	}
	return 0;
}
/*
2 3 1
1 0 1 0 0 0

3 3 2
1 0 0
0 0 0
0 0 0
*/
