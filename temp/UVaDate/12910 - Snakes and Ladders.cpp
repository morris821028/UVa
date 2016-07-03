#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <math.h>
using namespace std;

const int MAXN = 256;
double sol[MAXN];
int nosol[MAXN];
void gaussianElimination(double mtx[][MAXN], int n) {
#define eps 1e-8
    for (int i = 1; i <= n; i++) {
        int k = i;
        for (int j = i+1; j <= n; j++)
            if (fabs(mtx[k][i]) < fabs(mtx[j][i]))
            	k = j;
        if (fabs(mtx[k][i]) < eps)
        	continue;
        if (k != i) {
            for (int j = 1; j <= n+1; j++)
                swap(mtx[k][j], mtx[i][j]);
        }
        for (int j = 1; j <= n; j++) {
            if (i == j)  continue;
            for (int k = n+1; k >= i; k--) {
                mtx[j][k] -= mtx[j][i]/mtx[i][i]*mtx[i][k];
            }
        }
    }
    memset(nosol, 0, sizeof(nosol));
    for (int i = n; i >= 1; i--) {
        if (fabs(mtx[i][n+1]) > eps && fabs(mtx[i][i]) < eps)
            nosol[i] = 1;
        else {
            if (fabs(mtx[i][n+1]) < eps)
                sol[i] = 0;
            else
                sol[i] = mtx[i][n+1]/mtx[i][i];
        }
        for (int j = i+1; j <= n; j++)
            if (fabs(mtx[i][j]) > eps && nosol[j])
                nosol[i] = 1;
    }
}

double mtx[MAXN][MAXN];
int main() {
    int W, H, S;
    while(scanf("%d %d %d", &W, &H, &S) == 3) {
        vector<int> invg[MAXN];
        int deg[MAXN] = {}, u, v;
        
        int move[MAXN] = {};
        for (int i = 0; i < S; i++) {
        	scanf("%d %d", &u, &v); // u->v
        	move[u] = v;
        }
		
		for (int i = 1; i < W * H; i++) {
			for (int j = 1; j <= 6; j++) {
				if (i + j <= W * H) {
					u = i, v = i+j;
				} else {
					u = i, v = W*H - abs(W*H - (i+j));
//					continue;
				}
				if (move[v])	v = move[v];
//				printf("%d -> %d\n", v, u);
        		deg[u]++;
        		invg[u].push_back(v);
			}
		}
		
		int n = H * W;
        memset(mtx, 0, sizeof(mtx));
        
        for (int i = 1; i <= n; i++) {
            mtx[i][i] = 1;
            for (int j = 0; j < invg[i].size(); j++)
                mtx[i][invg[i][j]] -= 1.0/6;
            mtx[i][n+1] = 1;
        }
        
        gaussianElimination(mtx, n);
        
        printf("%.8lf\n", sol[1] - 1);
//        for (int i = 1; i <= n; i++)
//        	printf("%d %lf %d\n", i, sol[i], nosol[i]);
    }
    return 0;
}
/*
E[j] = sigma(E[i]*(1/deg[i])) + 1, if i->j exists.

7 1 0

6 5 0

6 5 8
3 22
17 4
5 8
19 7
21 9
11 26
27 1
20 29
*/
