#include <stdio.h> 
#include <math.h>
#include <algorithm>
using namespace std;

void gaussianElimination(double mtx[][16], int n, double sol[], int nosol[]) {
#define eps 1e-6
	int i, j;
	for(i = 0; i < n; i++) {
		int k = i;
		for(j = i; j < n; j++)
			if(fabs(mtx[k][i]) < fabs(mtx[j][i]))
				k = j;
		if(fabs(mtx[k][i]) < eps)
			continue;
		if(k != i) {
			for(j = 0; j <= n; j++)
				swap(mtx[k][j], mtx[i][j]);
		}
		for(j = 0; j < n; j++) {
			if(i == j) continue;
			for(k = n; k >= i; k--) {
				mtx[j][k] -= mtx[j][i]/mtx[i][i]*mtx[i][k];
			}
		}
	}
	for(int i = 0; i < n; i++)
		nosol[i] = 0;
	for(i = n-1; i >= 0; i--) {
		if(fabs(mtx[i][i]) < eps)
			nosol[i] = 1;
		else {
			if(fabs(mtx[i][n]) < eps)	sol[i] = 0;
			else						sol[i] = mtx[i][n]/mtx[i][i];
		}
		for(j = i+1; j < n; j++)
			if(fabs(mtx[i][j]) > eps && nosol[j])
			nosol[i] = 1;
	}
}
int main() {
	int testcase, cases = 0;
	double f[16][16], ret[16];
	int sol[16];
	scanf("%d", &testcase);
	while (testcase--) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++)
				scanf("%lf", &f[i][j]);
		}
		gaussianElimination(f, 3, ret, sol);
		printf("Case %d: %.2lf %.2lf %.2lf\n", ++cases, ret[0], ret[1], ret[2]);
	}
	return 0;
}
/*
2
3 3 1 20.00
6 0 2 20.00
6 4 0 20.00
3 0 1 6.00
0 2 2 10.00
1 3 1 10.00
*/
