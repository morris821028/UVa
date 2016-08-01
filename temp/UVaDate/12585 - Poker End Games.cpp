#include <stdio.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <math.h>
#include <queue>
#include <map>
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
vector<int> invg[MAXN];
int deg[MAXN] = {};
int buildGraph(int A, int B) {
	for (int i = 0; i < MAXN; i++)
		invg[i].clear(), deg[i] = 0;
	
	queue<int> X, Y;
	map< pair<int, int>, int> R;
	int label = 1, u, v;
	X.push(A), Y.push(B), R[make_pair(A, B)] = 1;
	
	while (!X.empty()) {
		A = X.front(), X.pop();
		B = Y.front(), Y.pop();
//		printf("%d %d\n", A, B);
		int C = min(A, B);
		if (!R.count(make_pair(A - C, B + C)))
			R[make_pair(A - C, B + C)] = ++label, X.push(A - C), Y.push(B + C);
		if (!R.count(make_pair(A + C, B - C)))
			R[make_pair(A + C, B - C)] = ++label, X.push(A + C), Y.push(B - C);
			
		u = R[make_pair(A, B)];
		v = R[make_pair(A - C, B + C)];
		if (u != v) {
			deg[u]++;
    		invg[u].push_back(v);
    	}
    		
		v = R[make_pair(A + C, B - C)];    	
    	if (u != v) {
    		deg[u]++;
    		invg[u].push_back(v);
    	}
	}
	return label;
}
int main() {
    int testcase, cases = 0;
	int A, B;
    scanf("%d", &testcase);
    while(testcase--) {
    	scanf("%d %d", &A, &B);
    	
    	int n = buildGraph(A, B);
    	
        memset(mtx, 0, sizeof(mtx));
        
        for (int i = 1; i <= n; i++) {
            mtx[i][i] = 1;
            for (int j = 0; j < invg[i].size(); j++)
                mtx[i][invg[i][j]] -= 1.0/2;
            mtx[i][n+1] = 1;
        }
        
        gaussianElimination(mtx, n);
        
        printf("Case %d: %.6lf %.6lf\n", ++cases, sol[1] - 1, (double) (A) / (A+B));
    }
    return 0;
}
/*
E[j] = sigma(E[i]*(1/deg[i])) + 1, if i->j exists.

6
42 6
4 8
6 5
9 6
1 1
0 5

999
1 1
2 1

*/
