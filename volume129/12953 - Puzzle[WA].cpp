#include <bits/stdc++.h>
using namespace std;

class GAUSSIAN { // Gaussian Elimination
public:
    static const int MAXN = 1024, MAXM = 208;
    long double mtx[MAXM][MAXN+1], varx[MAXN];
    int exist[MAXN], n, m;
    void compute(int var, int equ) {
        const double eps = 1e-12;
        this->n = var, this->m = equ;
        int row = 0, col = 0, arb = 0;
        while (row < equ && col < var) {
        	int c = row;
        	for (int i = row; i < equ; i++)
        		if (fabs(mtx[i][col]) > eps)	
					c = i;
        	for (int i = 0; i <= var; i++)
        		swap(mtx[c][i], mtx[row][i]);
        	if (mtx[row][col] == 0) {
        		col++, arb++;
        		continue;
        	}
        	for (int i = 0; i < equ; i++) {
        		if (i == row)	continue;
        		for (int j = var; j >= 0; j--)
        			mtx[i][j] -= mtx[i][col]/mtx[row][col]*mtx[row][j];
        	}
        	row++, col++;
        }
        for (int i = 0; i < n; i++)
            exist[i] = 1;
        for (int i = n-1; i >= 0; i--) {
            /* if (fabs(mtx[i][i]) < eps) {
                exist[i] = 0;
                continue;
            }
            if (fabs(mtx[i][n]) < eps)
                varx[i] = 0;
            else */
                varx[i] = mtx[i][n]/mtx[i][i];
            /* for (int j = i+1; j < n; j++)
                if (fabs(mtx[i][j]) > eps && exist[j])
                    exist[i] = 0; */
        }
    }
} tool;
int main() {
	int n, m;
	char s[128][128][8];
	while (scanf("%d %d", &n, &m) == 2) {
		int rsum[128], csum[128];
		map<string, int> R;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				scanf("%s", &s[i][j]), R[s[i][j]] = 0;
			scanf("%d", &rsum[i]);
		}
		for (int j = 0; j < m; j++)
			scanf("%d", &csum[j]);
		
		int size = 0, equ = 0;
		for (map<string, int>::iterator it = R.begin();
			it != R.end(); it++)
			it->second = size++;
		
		for (int i = 0; i < n+m; i++)
			for (int j = 0; j <= size; j++)
				tool.mtx[i][j] = 0;
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				tool.mtx[equ][R[s[i][j]]]++;
			tool.mtx[equ][size] = rsum[i], equ++;
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++)
				tool.mtx[equ][R[s[j][i]]]++;
			tool.mtx[equ][size] = csum[i], equ++;
		}
		
		tool.compute(size, equ);
		
		for (map<string, int>::iterator it = R.begin();
			it != R.end(); it++)
			printf("%s %.0lf\n", it->first.c_str(), (double) tool.varx[it->second]);
	}
	return 0;
}
